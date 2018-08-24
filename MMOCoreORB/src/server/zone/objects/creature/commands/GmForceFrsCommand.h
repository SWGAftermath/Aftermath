/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GMForceFrsCOMMAND_H_
#define GMForceFrsCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/frs/FrsManager.h"

class GmForceFrsCommand : public QueueCommand {
public:

	GmForceFrsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isCreatureObject())
			return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		Locker clocker(targetCreature, creature);

		ManagedReference<PlayerObject*> targetGhost = targetCreature->getPlayerObject();
		if(targetGhost == NULL)
			return INVALIDTARGET;

		StringTokenizer args(arguments.toString());

		int councilType = args.getIntToken();

		FrsManager* frsManager = targetGhost->getZoneServer()->getFrsManager();

		if (frsManager != nullptr && targetGhost != nullptr)
			Locker locker(targetGhost);

		FrsData* frsData = targetGhost->getFrsData();
		frsData->setCouncilType(councilType);
		frsManager->setPlayerRank(targetCreature, 0);

		return SUCCESS;
	}

};

#endif //GMForceFrsCOMMAND_H_