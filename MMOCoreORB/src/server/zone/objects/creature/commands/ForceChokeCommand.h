/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCECHOKECOMMAND_H_
#define FORCECHOKECOMMAND_H_

#include "ForcePowersQueueCommand.h"

class ForceChokeCommand : public ForcePowersQueueCommand {
protected:
	String tarSkillName = "forcechoke"; // Skill Name
	int tarDelay = 31;
public:

	ForceChokeCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET;
		}
		CreatureObject* targetCreature = dynamic_cast<CreatureObject*>(targetObject.get());

		if (!targetCreature->checkCooldownRecovery(tarSkillName)){
			Time* timeRemaining = targetCreature->getCooldownTime(tarSkillName);
			creature->sendSystemMessage("Target is already afflicted with Force Choke for another " + getCooldownString(timeRemaining->miliDifference() * -1) + " seconds");
			return GENERALERROR;
		}
		int res = doCombatAction(creature, target);

		if (res == SUCCESS) 
			targetCreature->updateCooldownTimer(tarSkillName, tarDelay * 1000);

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

#endif //FORCECHOKECOMMAND_H_
