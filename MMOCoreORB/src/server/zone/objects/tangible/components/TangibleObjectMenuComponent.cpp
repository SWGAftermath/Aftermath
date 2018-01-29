/*
 * TangibleObjectMenuComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "TangibleObjectMenuComponent.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/loot/LootGroupMap.h"

void TangibleObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	ObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	uint32 gameObjectType = sceneObject->getGameObjectType();

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>( sceneObject);

	// Figure out what the object is and if its able to be Sliced.
	if(tano->isSliceable() && !tano->isSecurityTerminal()) { // Check to see if the player has the correct skill level

		bool hasSkill = true;
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if ((gameObjectType == SceneObjectType::PLAYERLOOTCRATE) && !player->hasSkill("combat_smuggler_novice"))
			hasSkill = false;
		else if (sceneObject->isContainerObject())
			hasSkill = false; // Let the container handle our slice menu
		else if (sceneObject->isMissionTerminal() && !player->hasSkill("combat_smuggler_slicing_01"))
			hasSkill = false;
		else if (sceneObject->isWeaponObject() && (!inventory->hasObjectInContainer(sceneObject->getObjectID()) || !player->hasSkill("combat_smuggler_slicing_02")))
			hasSkill = false;
		else if (sceneObject->isArmorObject() && (!inventory->hasObjectInContainer(sceneObject->getObjectID()) || !player->hasSkill("combat_smuggler_slicing_03")))
			hasSkill = false;

		if(hasSkill)
			menuResponse->addRadialMenuItem(69, 3, "@slicing/slicing:slice"); // Slice
	}

	if(player->getPlayerObject() != NULL && player->getPlayerObject()->isPrivileged()) {
		/// Viewing components used to craft item, for admins
		ManagedReference<SceneObject*> container = tano->getSlottedObject("crafted_components");
		if(container != NULL) {

			if(container->getContainerObjectsSize() > 0) {

				SceneObject* satchel = container->getContainerObject(0);

				if(satchel != NULL && satchel->getContainerObjectsSize() > 0) {
					menuResponse->addRadialMenuItem(79, 3, "@ui_radial:ship_manage_components"); // View Components
				}
			}
		}
	}

	WearableObject* wearable = cast<WearableObject*>(tano);
	if (wearable != NULL)
	if (wearable->hasSeaRemovalTool(player, false) ==  true)
	if (wearable->isWearableObject() || wearable->isArmorObject()){
		VectorMap<String, int>* mods = wearable->getWearableSkillMods();
			if (mods->size() > 0)
				menuResponse->addRadialMenuItem(89,3,"Extract Skill Mods");
		}
	

	ManagedReference<SceneObject*> parent = tano->getParent().get();
	if (parent != NULL && parent->getGameObjectType() == SceneObjectType::STATICLOOTCONTAINER) {
		menuResponse->addRadialMenuItem(10, 3, "@ui_radial:item_pickup"); //Pick up
	}
}

int TangibleObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isTangibleObject())
		return 0;

	TangibleObject* tano = cast<TangibleObject*>( sceneObject);


	if (selectedID == 69 && player->hasSkill("combat_smuggler_novice") ) { // Slice [PlayerLootCrate]
		if (player->containsActiveSession(SessionFacadeType::SLICING)) {
			player->sendSystemMessage("@slicing/slicing:already_slicing");
			return 0;
		}

		//Create Session
		ManagedReference<SlicingSession*> session = new SlicingSession(player);
		session->initalizeSlicingMenu(player, tano);

		return 0;
	} else if (selectedID == 79) { // See components (admin)
		if(player->getPlayerObject() != NULL && player->getPlayerObject()->isPrivileged()) {

			SceneObject* container = tano->getSlottedObject("crafted_components");
			if(container != NULL) {

				if(container->getContainerObjectsSize() > 0) {

					SceneObject* satchel = container->getContainerObject(0);

					if(satchel != NULL) {

						satchel->sendWithoutContainerObjectsTo(player);
						satchel->openContainerTo(player);

					} else {
						player->sendSystemMessage("There is no satchel this container");
					}
				} else {
					player->sendSystemMessage("There are no items in this container");
				}
			} else {
				player->sendSystemMessage("There is no component container in this object");
			}
		}

		return 0;
	} else if (selectedID == 89) { //Remove SEA Mods from wearable
		
		WearableObject* wearable = cast<WearableObject*>(tano);
		ManagedReference<SceneObject*> sea = NULL;
		bool convertedMods = false;
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
			if (wearable != NULL && inventory != NULL) { //safety Checks

			if (wearable->hasSeaRemovalTool(player, false) ==  false){ //They need the tool
				player->sendSystemMessage("This requires a specialzied skill enhancing attachment removal tool.");
				return 0;
			}

			if (wearable->isWearableObject() || wearable->isArmorObject()){
				if (wearable->isEquipped()){
				player->sendSystemMessage("You must first un-equip the item.");
				return 0;
				}
				VectorMap<String, int>* mods = wearable->getWearableSkillMods();
					if (mods->size() > 0){	//If the item has no mods we're done
						ManagedReference<LootManager*> lootManager = player->getZoneServer()->getLootManager();		
						int i,j;
						LootGroupMap* lootGroupMap = LootGroupMap::instance();
						Reference<LootItemTemplate*> itemTemplate = NULL;
						String objectTemplate = "";
						objectTemplate = sceneObject->getObjectTemplate()->getFullTemplateString();
						
						//error("ObjectTempate = " + objectTemplate);
						if (wearable->isArmorObject() || 
						 objectTemplate == "object/tangible/wearables/armor/padded/armor_padded_s01_belt.iff"  || 
						 objectTemplate == "object/tangible/wearables/armor/zam/armor_zam_wesell_belt.iff"){
							//error("Detected as armor or belt");
							itemTemplate = lootGroupMap->getLootItemTemplate("attachment_armor");
						}
						else{
							//error("detect as clothing");
							itemTemplate = lootGroupMap->getLootItemTemplate("attachment_clothing");
						}
						if (lootGroupMap == NULL){
						error("Invalid loot template");
						return 0;
						}
						for (i=0;i<mods->size();i++){//Remove skill mods from item and create tapes
							
							String modKey = mods->elementAt(i).getKey();

							sea = lootManager->createLootAttachment(itemTemplate,modKey, mods->elementAt(i).getValue()); 

							if (sea != NULL){
								Attachment* attachment = cast<Attachment*>(sea.get());
								
								if (attachment != NULL){
									Locker objLocker(attachment);
									if (inventory->transferObject(sea, -1, true, true)) { //Transfer tape to player inventory
										inventory->broadcastObject(sea, true);
									} else {
										sea->destroyObjectFromDatabase(true);
										error("Unable to place Skill Attachment in player's inventory!");
										return false;
									}
									
								}
								
							}
						}
						//Destroy item now that tapes have been generated
						if (wearable->hasSeaRemovalTool(player,true) ==  true)
							player->sendSystemMessage("Your SEA Tool has been consumed in the process.");
						wearable->destroyObjectFromWorld(true);
						wearable->destroyObjectFromDatabase(true);		
						player->sendSystemMessage("Removing SEA");
						if (convertedMods)
							player->sendSystemMessage("Old skill mods were converted to new skill mods.");
					}	
			}
		}

		
	return 0;
	} else
		return ObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

}

