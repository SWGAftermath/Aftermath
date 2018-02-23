/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DISARMINGSHOT2COMMAND_H_
#define DISARMINGSHOT2COMMAND_H_

#include "CombatQueueCommand.h"

class DisarmingShot2Command : public CombatQueueCommand {
public:

	DisarmingShot2Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		CreatureObject* targetCreature = dynamic_cast<CreatureObject*>(object.get());

		if (targetCreature == NULL)
			return INVALIDTARGET;

		Locker clocker(targetCreature, creature);

		ManagedReference<PlayerObject*> player = creature->getPlayerObject();
		PlayerObject* targetPlayerObject = targetCreature->getPlayerObject();

		if (targetPlayerObject == NULL) {
			return INVALIDTARGET;
		} else if (player == NULL)
			return GENERALERROR;
		
		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			// Setup debuff.


			if (targetCreature != NULL) {
				Locker clocker(targetCreature, creature);

				ManagedReference<Buff*> buff = new Buff(targetCreature, getNameCRC(), 10, BuffType::OTHER);

				Locker locker(buff);

				buff->setSpeedMultiplierMod(speed);
				buff->setAccelerationMultiplierMod(speed);
				targetCreature->setRootedState(10);

				targetCreature->addBuff(buff);

			}

		}
		return res;
	}

};

#endif //DISARMINGSHOT2COMMAND_H_
