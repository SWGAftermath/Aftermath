/*
 * ArmorObjectMenuComponent.cpp
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"
#include "ArmorObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/callbacks/ColorArmorSuiCallback.h"
#include "server/zone/ZoneServer.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"

void ArmorObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if (!sceneObject->isWearableObject())
		return;

	ManagedReference<SceneObject*> parent = sceneObject->getParent().get();

	if (parent != NULL && parent->isCellObject()) {
		ManagedReference<SceneObject*> obj = parent->getParent().get();

		if (obj != NULL && obj->isBuildingObject()) {
			ManagedReference<BuildingObject*> buio = cast<BuildingObject*>(obj.get());

			if (!buio->isOnAdminList(player))
				return;
		}
	}
	else
	{
		if (!sceneObject->isASubChildOf(player))
			return;
	}

	if (!parent->isPlayerCreature()) {
				menuResponse->addRadialMenuItem(81, 3, "Modify Color");	
		}
	
    WearableObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player); 	
}

int ArmorObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {

	if (selectedID == 81) {
		
		ManagedReference<SceneObject*> parent = sceneObject->getParent().get();
	
		if (parent == NULL)
			return 0;
	
		if (parent->isPlayerCreature()) {
			player->sendSystemMessage("@armor_rehue:equipped");
			return 0;
		}	

		if (parent->isCellObject()) {
			ManagedReference<SceneObject*> obj = parent->getParent().get();

			if (obj != NULL && obj->isBuildingObject()) {
				ManagedReference<BuildingObject*> buio = cast<BuildingObject*>(obj.get());

				if (!buio->isOnAdminList(player))
					return 0;
			}
		}
		else
		{
			if (!sceneObject->isASubChildOf(player))
				return 0;
		}

		ZoneServer* server = player->getZoneServer();

		if (server != NULL) 
		{		

		// The color index.
		String appearanceFilename = sceneObject->getObjectTemplate()->getAppearanceFilename();
		VectorMap<String, Reference<CustomizationVariable*> > variables;
		AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);

		for(int i = 0; i < variables.size(); i++)
		{
			String varkey = variables.elementAt(i).getKey();
				if (varkey.contains("color")) 
				{
					
					// The Sui Box.
					ManagedReference<SuiColorBox*> cbox = new SuiColorBox(player, SuiWindowType::COLOR_ARMOR);
					cbox->setCallback(new ColorArmorSuiCallback(server));
					cbox->setColorPalette(variables.elementAt(i).getKey()); // First one seems to be the frame of it? Skip to 2nd.
					cbox->setUsingObject(sceneObject);

					// Make Color number the title of the SUI Box
					cbox->setPromptTitle("Color " + String::valueOf(i + 1));

					// Add to player.
					ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
					ghost->addSuiBox(cbox);
					player->sendMessage(cbox->generateMessage());
					
				}
		}
		}
	}
	
	return WearableObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}