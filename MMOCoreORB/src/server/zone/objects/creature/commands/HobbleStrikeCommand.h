/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HOBBLESTRIKECOMMAND_H_
#define HOBBLESTRIKECOMMAND_H_

#include "CombatQueueCommand.h"

class HobbleStrikeCommand : public CombatQueueCommand {

protected:
	String skillName = "hobblestrike";		        // Skill Name
	String tarSkillName = "tarHobbleStrike";
	String skillNameDisplay = "Hobble Strike";		// Skill Display Name for output message
	int delay = 30; 							//  30 second cool down timer after root expires
	int tarDelay = 20;

public:

	HobbleStrikeCommand(const String& name, ZoneProcessServer* server)
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

		if (!creature->checkCooldownRecovery(skillName)){
			Time* timeRemaining = creature->getCooldownTime(skillName);
			creature->sendSystemMessage("You must wait " +  getCooldownString(timeRemaining->miliDifference() * -1)  + " to use " + skillNameDisplay + " again");
			return GENERALERROR;
		}

		if (!targetCreature->checkCooldownRecovery(tarSkillName)){
			Time* timeRemaining = targetCreature->getCooldownTime(tarSkillName);
			creature->sendSystemMessage("You cannot use " + skillNameDisplay + " on target for " + getCooldownString(timeRemaining->miliDifference() * -1));
			return GENERALERROR;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			// Setup debuff.


			if (targetCreature != NULL) {
				Locker clocker(targetCreature, creature);

				ManagedReference<Buff*> buff = new Buff(targetCreature, getNameCRC(), 5, BuffType::OTHER);

				Locker locker(buff);
				if (targetCreature->hasBuff(BuffCRC::JEDI_FORCE_RUN_1)) {
					targetCreature->removeBuff(BuffCRC::JEDI_FORCE_RUN_1);
				}

				targetCreature->setSnaredState(5);
				StringBuffer targetRootMessage;

				targetRootMessage << "Your body has been weakened and you can't use the force to run for 5 seconds";
				targetCreature->sendSystemMessage(targetRootMessage.toString());

				targetCreature->addBuff(buff);
				creature->updateCooldownTimer(skillName, delay * 1000);
				targetCreature->updateCooldownTimer(tarSkillName, tarDelay * 1000);

			}

		}
		return res;
	}

	String getCooldownString(uint32 delta) const {

		int seconds = delta / 1000;

		int hours = seconds / 3600;
		seconds -= hours * 3600;

		int minutes = seconds / 60;
		seconds -= minutes * 60;

		StringBuffer buffer;

		if (hours > 0)
			buffer << hours << "h ";

		if (minutes > 0)
			buffer << minutes << "m ";

		if (seconds > 0)
			buffer << seconds << "s";

		return buffer.toString();
	}

};

#endif //HOBBLESTRIKECOMMAND_H_
