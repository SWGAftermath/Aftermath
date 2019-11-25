/*
 * PackupStructureSessionImplementation.cpp
 */

#include "server/zone/objects/player/sessions/PackupStructureSession.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/PackupStructureCodeSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/PackupStructureRequestSuiCallback.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/Zone.h"

int PackupStructureSessionImplementation::initializeSession() {
	//TODO: Temporary until CreatureObject* dependency removed.
	if (!creatureObject->isPlayerCreature())
		return cancelSession();

	creatureObject->addActiveSession(SessionFacadeType::PACKUPSTRUCTURE, _this.getReferenceUnsafeStaticCast());

	Locker _lock(structureObject, creatureObject);

	CreatureObject* player = cast<CreatureObject*>( creatureObject.get());

	String no = "\\#FF6347 @player_structure:can_redeed_no_suffix \\#.";
	String yes = "\\#32CD32 @player_structure:can_redeed_yes_suffix \\#.";

	String redeed = (structureObject->isRedeedable()) ? yes : no;

	StringBuffer maint;
	maint << "@player_structure:redeed_maintenance \\#" << ((structureObject->isRedeedable()) ? "32CD32 " : "FF6347 ") << structureObject->getSurplusMaintenance() << "/" << structureObject->getRedeedCost() << "\\#.";

	StringBuffer entry;
	entry << "@player_structure:confirm_packup_d1 ";
	entry << "@player_structure:confirm_packup_d2 \n\n";
	entry << "@player_structure:confirm_packup_d3a ";
	entry << "\\#32CD32 @player_structure:confirm_packup_d3b \\#. ";
	entry << "@player_structure:confirm_packup_d4 \n\n";
	entry << "@player_structure:packup_confirmation " << redeed;

	StringBuffer cond;
	cond << "@player_structure:redeed_condition \\#32CD32 " << (structureObject->getMaxCondition() - structureObject->getConditionDamage()) << "/" << structureObject->getMaxCondition() << "\\#.";

	ManagedReference<SuiListBox*> sui = new SuiListBox(player);
	sui->setCallback(new PackupStructureRequestSuiCallback(creatureObject->getZoneServer()));
	sui->setCancelButton(true, "@no");
	sui->setOkButton(true, "@yes");
	sui->setUsingObject(structureObject);
	sui->setPromptTitle(structureObject->getDisplayedName());
	sui->setPromptText(entry.toString());

	sui->addMenuItem("@player_structure:can_packup_alert " + redeed);
	sui->addMenuItem(cond.toString());
	sui->addMenuItem(maint.toString());

	player->getPlayerObject()->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());

	return 0;
}

int PackupStructureSessionImplementation::sendPackupCode() {
	//TODO: Temporary until CreatureObject* dependency removed.
	if (!creatureObject->isPlayerCreature())
		return cancelSession();

	Locker structureLock(structureObject);

	Locker _lock(creatureObject, structureObject);

	CreatureObject* player = cast<CreatureObject*>( creatureObject.get());

	packupCode = System::random(899999) + 100000;

	String no = "\\#FF6347 @player_structure:will_not_redeed_confirm \\#.";
	String yes = "\\#32CD32 @player_structure:will_redeed_confirm \\#.";
	String redeed = (structureObject->isRedeedable()) ? yes : no;

	StringBuffer entry;
	entry << "@player_structure:your_structure_prefix ";
	entry << redeed << " @player_structure:will_packup_suffix \n\n";
	entry << "Code: " << packupCode;

	ManagedReference<SuiInputBox*> sui = new SuiInputBox(player);
	sui->setCallback(new PackupStructureCodeSuiCallback(player->getZoneServer()));
	sui->setUsingObject(structureObject);
	sui->setPromptTitle("@player_structure:confirm_packup_t");
	sui->setPromptText(entry.toString());
	sui->setCancelButton(true, "@cancel");
	sui->setMaxInputSize(6);

	player->getPlayerObject()->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());

	return 0;
}

int PackupStructureSessionImplementation::packupStructure() {
	creatureObject->sendSystemMessage("@player_structure:processing_packup");

	if (structureObject == nullptr || structureObject->getZone() == nullptr)
		return cancelSession();

	if (!structureObject->isRedeedable()) {
		creatureObject->sendSystemMessage("@player_structure:packup_items_maint");
		return cancelSession();
	}

	StructureManager::instance()->packupStructure(creatureObject);
	return 0;
}
