/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTSETSTATMIGRATIONDATACOMMAND_H_
#define REQUESTSETSTATMIGRATIONDATACOMMAND_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/MigrateStatsSession.h"
#include "server/zone/managers/player/creation/PlayerCreationManager.h"

class RequestSetStatMigrationDataCommand : public QueueCommand {
protected:
	String skillName = "setStatMigration";		// Skill Name

	String skillNameDisplay = "Stat Migration";		// Skill Display Name for output message
	int delay = 10800; 								//  3 hrs
public:

	RequestSetStatMigrationDataCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	static uint32 getMaxAttribute(CreatureObject* creature, uint8 attribute) {
		return PlayerCreationManager::instance()->getMaximumAttributeLimit(creature->getSpeciesName(), attribute);
	}

	static uint32 getMinAttribute(CreatureObject* creature, uint8 attribute) {
		return PlayerCreationManager::instance()->getMinimumAttributeLimit(creature->getSpeciesName(), attribute);
	}

	static uint32 getTotalAttribPoints(CreatureObject* creature) {
		return PlayerCreationManager::instance()->getTotalAttributeLimit(creature->getSpeciesName());
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);
		PlayerObject* ghost = player->getPlayerObject();

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::MIGRATESTATS);
		ManagedReference<MigrateStatsSession*> session = dynamic_cast<MigrateStatsSession*>(facade.get());

		if (session == NULL) {
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		uint32 targetPointsTotal = 0;
		uint32 targetAttributes[9] = {0,0,0,0,0,0,0,0,0};

		for (int i = 0; tokenizer.hasMoreTokens() && i < 9; ++i) {
			uint32 value = tokenizer.getIntToken();

			if (value < getMinAttribute(player, i) || value > getMaxAttribute(player, i)) {
				creature->info("Suspected stat migration hacking attempt.");
				return GENERALERROR;
			}

			targetAttributes[i] = value;
			targetPointsTotal += value;
		}

		//Here we set the stat migration target attributes.
		//NOTE: We aren't actually migrating the stats at this point.
		if (targetPointsTotal == getTotalAttribPoints(player)) {
			for (int i = 0; i < 9; ++i) {
				session->setAttributeToModify(i, targetAttributes[i]);
			}
		} else {
			creature->error("targetPointsTotal = " + String::valueOf(targetPointsTotal));
			creature->error("totalAttribPoints = " + String::valueOf(getTotalAttribPoints(player)));
			creature->error("Trying to set migratory stats without assigning all available points.");
			return GENERALERROR;
		}

		/*if (!creature->checkCooldownRecovery(skillName)){
			Time* timeRemaining = creature->getCooldownTime(skillName);
			creature->sendSystemMessage("You must wait " + getCooldownString(timeRemaining->miliDifference() *  -1) + " to use " + skillNameDisplay + " again");
			return GENERALERROR;
		}*/
		Zone* zone = creature->getZone();
		uint32 focusBuffCRC = STRING_HASHCODE("performance_enhance_music_focus");
		uint32 willBuffCRC = STRING_HASHCODE("performance_enhance_music_willpower");
		uint32 mindBuffCRC = STRING_HASHCODE("performance_enhance_dance_mind");
		if (zone != NULL && !player->isInCombat() && !creature->hasBuff(focusBuffCRC) && !creature->hasBuff(willBuffCRC) && !creature->hasBuff(mindBuffCRC)){
			session->migrateStats();
			/*creature->updateCooldownTimer(skillName, delay * 1000);*/
			return SUCCESS;
		}else{
			creature->sendSystemMessage("You cannot migrate stats while buffed, please reset your buffs before migrating");
			return GENERALERROR;	
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

#endif //REQUESTSETSTATMIGRATIONDATACOMMAND_H_
