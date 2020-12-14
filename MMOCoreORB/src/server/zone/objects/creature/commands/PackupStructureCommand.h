/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PACKUPSTRUCTURECOMMAND_H_
#define PACKUPSTRUCTURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/player/sessions/PackupStructureSession.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"

class PackupStructureCommand : public QueueCommand {
public:

	PackupStructureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->containsActiveSession(SessionFacadeType::PACKUPSTRUCTURE)) {
			creature->sendSystemMessage("@player_structure:pending_packup");
			return GENERALERROR;
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		uint64 targetid = creature->getTargetID();
		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, targetid);

		if (obj == nullptr || !obj->isStructureObject())
			return INVALIDTARGET;

		StructureObject* structure = cast<StructureObject*>( obj.get());

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		if (!ghost->isOwnedStructure(structure) && !ghost->isStaff()) {
			creature->sendSystemMessage("@player_structure:packup_must_be_owner");
			return INVALIDTARGET;
		}

		if (!ConfigManager::instance()->getStructurePackupEnabled()) {
			creature->sendSystemMessage("@player_structure:packup_not_eligible_01");
			return INVALIDTARGET;
		}

		String message = structure->getPackupMessage();
		if (!message.isEmpty()) {
			creature->sendSystemMessage("@player_structure:" + message);
			return INVALIDTARGET;
		}

		ManagedReference<PackupStructureSession*> session = new PackupStructureSession(creature, structure);
		session->initializeSession();

		return SUCCESS;
	}
};

#endif //PACKUPSTRUCTURECOMMAND_H_
