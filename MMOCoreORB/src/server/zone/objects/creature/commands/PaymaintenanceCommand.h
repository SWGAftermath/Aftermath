/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PAYMAINTENANCECOMMAND_H_
#define PAYMAINTENANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class PaymaintenanceCommand : public QueueCommand {
public:

	PaymaintenanceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getCashCredits() <= 0) {
			creature->sendSystemMessage("@player_structure:no_money"); //You do not have any money to pay maintenance.
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target).castTo<SceneObject*>();

		if (obj == nullptr || !obj->isStructureObject()) {
			ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
			uint64 targetid = creature->getTargetID();

			obj = playerManager->getInRangeStructureWithAdminRights(creature, targetid);
		}

		if (obj == nullptr || !obj->isStructureObject()) {
			creature->sendSystemMessage("@player_structure:no_building"); //you must be in a building, be near an installation, or have one targeted to do that.
			return INVALIDTARGET;
		}

		StructureObject* structure = cast<StructureObject*>(obj.get());

		Locker clocker(structure, creature);

		if (!structure->isOnAdminList(creature))
			return INVALIDTARGET;

		if (structure->isCivicStructure()) {
			creature->sendSystemMessage("@player_structure:civic_structure_alert"); // Civic structure: Maintenance handled by city.
			return INVALIDTARGET;
		}

		if (structure->isGCWBase()) {
			return INVALIDTARGET;
		}

		StructureManager* structureManager = StructureManager::instance();

		try {
			UnicodeTokenizer tokenizer(arguments);
			int amount = tokenizer.getIntToken();

			if (amount > 0)
				structureManager->payMaintenance(structure, creature, amount);
		} catch (Exception& e) {
			structureManager->promptPayMaintenance(structure, creature);
		}

		return SUCCESS;
	}

};

#endif //PAYMAINTENANCECOMMAND_H_
