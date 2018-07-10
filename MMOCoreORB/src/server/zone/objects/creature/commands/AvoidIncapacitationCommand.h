/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef AVOIDINCAPACITATIONCOMMAND_H_
#define AVOIDINCAPACITATIONCOMMAND_H_

#include "JediQueueCommand.h"

class AvoidIncapacitationCommand : public JediQueueCommand {

protected:
	String skillName = "avoidIncapacitation";		// Skill Name
	String skillNameDisplay = "Avoid Incap";		// Skill Display Name for output message
	int delay = 75; 								//  15 second cool down timer


public:

	AvoidIncapacitationCommand(const String& name, ZoneProcessServer* server)
: JediQueueCommand(name, server) {
		 buffCRC = BuffCRC::JEDI_AVOID_INCAPACITATION;
		 skillMods.put("avoid_incapacitation", 1);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		// SPECIAL - For Avoid Incapacitation, which is a special case buff, if it's determined that it should only be stacked up to 6 times for a new buff object, then it'll needs a new crc from the other 5 in string-files.
		// PLUS: There is no concrete evidence for what's stated in 'SPECIAL' sentence above, beyond the existence of 6 CRCs themselves.

		/*if (creature->hasBuff(BuffCRC::JEDI_AVOID_INCAPACITATION)) {

			int res = doCommonJediSelfChecks(creature);

			if (res != SUCCESS)
				return res;
blockingCRCs 
			creature->renewBuff(buffCRC, duration, true);

			doForceCost(creature);

			if (!clientEffect.isEmpty())
				creature->playEffect(clientEffect, "");

			return SUCCESS; */
		 if (creature->hasBuff(BuffCRC::JEDI_FORCE_ABSORB_1) || creature->hasBuff(BuffCRC::JEDI_FORCE_ABSORB_2)){
			creature->sendSystemMessage("Avoid Incapacitation cannot be used with Force Absorb");
			return GENERALERROR;

		} else if (!creature->checkCooldownRecovery(skillName)) {
			Time* timeRemaining = creature->getCooldownTime(skillName);
			creature->sendSystemMessage("You must wait " +  getCooldownString(timeRemaining->miliDifference() * -1)  + " to use " + skillNameDisplay + " again");
			return GENERALERROR;
		} else {
			int res = doJediSelfBuffCommand(creature);
			if (res != SUCCESS){
				return res;
			}else{
				creature->updateCooldownTimer(skillName, delay * 1000);
				return res;
			}
			
		}
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

#endif //AVOIDINCAPACITATIONCOMMAND_H_
