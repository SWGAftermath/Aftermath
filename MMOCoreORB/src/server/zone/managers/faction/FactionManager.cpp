/*
 * FactionManager.cpp
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#include "FactionManager.h"
#include "FactionMap.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/player/FactionStatus.h"

FactionManager::FactionManager() {
	setLoggingName("FactionManager");
	setGlobalLogging(false);
	setLogging(false);
}

void FactionManager::loadData() {
	loadLuaConfig();
	loadFactionRanks();
}

void FactionManager::loadFactionRanks() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/faction/rank.iff");

	if (iffStream == NULL) {
		warning("Faction ranks could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	factionRanks.readObject(&dtiff);

	delete iffStream;

	info("loaded " + String::valueOf(factionRanks.getCount()) + " ranks", true);
}

void FactionManager::loadLuaConfig() {
	info("Loading config file.", true);

	FactionMap* fMap = getFactionMap();

	Lua* lua = new Lua();
	lua->init();

	//Load the faction manager lua file.
	lua->runFile("scripts/managers/faction_manager.lua");

	LuaObject luaObject = lua->getGlobalObject("factionList");
	globalFactionMultiplier = lua->getGlobalFloat("globalFactionMultiplier");

	if (luaObject.isValidTable()) {
		for (int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject factionData = luaObject.getObjectAt(i);

			if (factionData.isValidTable()) {
				String factionName = factionData.getStringAt(1);
				bool playerAllowed = factionData.getBooleanAt(2);
				String enemies = factionData.getStringAt(3);
				String allies = factionData.getStringAt(4);
				float adjustFactor = factionData.getFloatAt(5);

				Faction faction(factionName);
				faction.setAdjustFactor(adjustFactor);
				faction.setPlayerAllowed(playerAllowed);
				faction.parseEnemiesFromList(enemies);
				faction.parseAlliesFromList(allies);

				fMap->addFaction(faction);
			}

			factionData.pop();
		}
	}

	luaObject.pop();

	delete lua;
	lua = NULL;
}

FactionMap* FactionManager::getFactionMap() {
	return &factionMap;
}

void FactionManager::awardFactionStanding(CreatureObject* player, const String& factionName, int level) {
	if (player == NULL)
		return;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (!factionMap.contains(factionName))
		return;

	const Faction& faction = factionMap.get(factionName);
	const SortedVector<String>* enemies = faction.getEnemies();
	const SortedVector<String>* allies = faction.getAllies();

	if (!faction.isPlayerAllowed())
		return;

	float gain = level * faction.getAdjustFactor() * globalFactionMultiplier;
	float lose = gain * 2;

	ghost->decreaseFactionStanding(factionName, lose);

	//Lose faction standing to allies of the creature.
	for (int i = 0; i < allies->size(); ++i) {
		const String& ally = allies->get(i);

		if ((ally == "rebel" || ally == "imperial")) {
			continue;
		}

		if (!factionMap.contains(ally))
			continue;

		const Faction& allyFaction = factionMap.get(ally);

		if (!allyFaction.isPlayerAllowed())
			continue;

		ghost->decreaseFactionStanding(ally, lose);
	}

	bool gcw = false;
	if (factionName == "rebel" || factionName == "imperial") {
		gcw = true;
	}

	//Gain faction standing to enemies of the creature.
	for (int i = 0; i < enemies->size(); ++i) {
		const String& enemy = enemies->get(i);

		if ((enemy == "rebel" || enemy == "imperial") && !gcw) {
			continue;
		}

		if (!factionMap.contains(enemy))
			continue;

		const Faction& enemyFaction = factionMap.get(enemy);

		if (!enemyFaction.isPlayerAllowed())
			continue;

		ghost->increaseFactionStanding(enemy, gain);
	}
}


void FactionManager::awardPvpFactionPoints(TangibleObject* killer, CreatureObject* destructedObject) {
	if (killer->isPlayerCreature() && destructedObject->isPlayerCreature()) {
		CreatureObject* killerCreature = cast<CreatureObject*>(killer);
		ManagedReference<PlayerObject*> ghost = killerCreature->getPlayerObject();
		ManagedReference<GroupObject*> group;

		ManagedReference<PlayerObject*> killedGhost = destructedObject->getPlayerObject();
		ManagedReference<PlayerManager*> playerManager = killerCreature->getZoneServer()->getPlayerManager();

		//Broadcast to Server
		String playerName = destructedObject->getFirstName();
		String killerName = killerCreature->getFirstName();
		StringBuffer zBroadcast;

		if (killer->isRebel() && destructedObject->isImperial()) {
			ghost->increaseFactionStanding("rebel", 30);
			ghost->decreaseFactionStanding("imperial", 45);

			killedGhost->decreaseFactionStanding("imperial", 45);
			playerManager->awardExperience(killerCreature, "gcw_currency_rebel", 1000);
			group = killerCreature->getGroup();
			Vector<ManagedReference<CreatureObject*> > players;
			int playerCount = 1;

			StringBuffer gcwKillQuery;
			Database::escapeString(playerName);
			Database::escapeString(killerName);
			int killerRating = ghost->getPvpRating();
			int playerRating = killedGhost->getPvpRating();
			String winner = "Rebel";
			gcwKillQuery << "INSERT INTO gcw_kills(killer, killer_rating, victim, victim_rating, winner) VALUES ('" << killerName <<"'," << killerRating << ", '" << playerName << "'," << playerRating << ", '" << winner << "');";
			ServerDatabase::instance()->executeStatement(gcwKillQuery);
			if (group != NULL){
				//Locker lockerGroup(group, _this.getReferenceUnsafeStaticCast());
				playerCount = group->getNumberOfPlayerMembers();
				for (int x=0; x< group->getGroupSize(); x++){
					Reference<CreatureObject*> groupMember = group->getGroupMember(x);
					//if (groupMember == killerCreature)
					//	continue;
					if (groupMember->isRebel() && groupMember->isPlayerCreature() && groupMember->isInRange(killerCreature, 128.0f) && (groupMember->getPlayerObject()->hasPvpTef() || groupMember->getPlayerObject()->hasJediTef() || groupMember->getFactionStatus() == FactionStatus::OVERT))
						players.add(groupMember);
				}
			} else {
				players.add(killerCreature);
			}

			if (players.size() == 0) {
				players.add(killerCreature);
			}

			if (playerCount > players.size()) {
				killerCreature->sendSystemMessage("Some players were too far away from the kill!"); // Mission Alert! Some group members are too far away from the group to receive their reward and and are not eligible for reward.
			}

			int dividedKill = 5000 / players.size();
			if (players.size() == 1)
				dividedKill = 2500;
			for (int i = 0; i < players.size(); i++){
				ManagedReference<CreatureObject*> player = players.get(i);
				ManagedReference<PlayerManager*> groupPlayerManager = player->getZoneServer()->getPlayerManager();
				groupPlayerManager->awardExperience(player, "gcw_currency_rebel", dividedKill);
				StringBuffer sysMessage;
				sysMessage << "You have received " << dividedKill << " GCW XP for your kill participation!";
				player->sendSystemMessage(sysMessage.toString());

			}

		} else if (killer->isImperial() && destructedObject->isRebel()) {
			ghost->increaseFactionStanding("imperial", 30);
			ghost->decreaseFactionStanding("rebel", 45);

			killedGhost->decreaseFactionStanding("rebel", 45);
			playerManager->awardExperience(killerCreature, "gcw_currency_imperial", 1000);
			group = killerCreature->getGroup();
			Vector<ManagedReference<CreatureObject*> > players;
			int playerCount = 1;
			StringBuffer gcwKillQuery;
			Database::escapeString(playerName);
			Database::escapeString(killerName);
			int killerRating = ghost->getPvpRating();
			int playerRating = killedGhost->getPvpRating();
			String winner = "Imperial";
			gcwKillQuery << "INSERT INTO gcw_kills(killer, killer_rating, victim, victim_rating, winner) VALUES ('" << killerName <<"'," << killerRating << ", '" << playerName << "'," << playerRating << ", '" << winner << "');";
			ServerDatabase::instance()->executeStatement(gcwKillQuery);
			if (group != NULL){
				//Locker lockerGroup(group, _this.getReferenceUnsafeStaticCast());
				playerCount = group->getNumberOfPlayerMembers();
				for (int x=0; x< group->getGroupSize(); x++){
					Reference<CreatureObject*> groupMember = group->getGroupMember(x);
					//if (groupMember == killerCreature)
					//	continue;
					if (groupMember->isImperial() && groupMember->isPlayerCreature() && groupMember->isInRange(killerCreature, 128.0f) && (groupMember->getPlayerObject()->hasPvpTef() || groupMember->getPlayerObject()->hasJediTef() || groupMember->getFactionStatus() == FactionStatus::OVERT))
						players.add(groupMember);
				}
			} else {
				players.add(killerCreature);
			}

			if (players.size() == 0) {
				players.add(killerCreature);
			}

			if (playerCount > players.size()) {
				killerCreature->sendSystemMessage("Some players were too far away from the kill!"); // Mission Alert! Some group members are too far away from the group to receive their reward and and are not eligible for reward.
			}

			int dividedKill = 5000 / players.size();
			if (players.size() == 1)
				dividedKill = 2500;
			for (int i = 0; i < players.size(); i++){
				ManagedReference<CreatureObject*> player = players.get(i);
				ManagedReference<PlayerManager*> groupPlayerManager = player->getZoneServer()->getPlayerManager();
				groupPlayerManager->awardExperience(player, "gcw_currency_imperial", dividedKill);
				StringBuffer sysMessage;
				sysMessage << "You have received " << dividedKill << " GCW XP for your kill participation!";
				player->sendSystemMessage(sysMessage.toString());

			}
		}
	}
}

String FactionManager::getRankName(int idx) {
	if (idx >= factionRanks.getCount())
		return "";

	return factionRanks.getRank(idx).getName();
}

int FactionManager::getRankCost(int rank) {
	if (rank >= factionRanks.getCount())
		return -1;

	return factionRanks.getRank(rank).getCost();
}

int FactionManager::getRankDelegateRatioFrom(int rank) {
	if (rank >= factionRanks.getCount())
		return -1;

	return factionRanks.getRank(rank).getDelegateRatioFrom();
}

int FactionManager::getRankDelegateRatioTo(int rank) {
	if (rank >= factionRanks.getCount())
		return -1;

	return factionRanks.getRank(rank).getDelegateRatioTo();
}

int FactionManager::getFactionPointsCap(int rank) {
	if (rank >= factionRanks.getCount())
		return -1;

	return Math::max(1000, getRankCost(rank) * 20);
}

bool FactionManager::isFaction(const String& faction) {
	if (factionMap.contains(faction))
		return true;

	return false;
}

bool FactionManager::isEnemy(const String& faction1, const String& faction2) {

	if (!factionMap.contains(faction1) || !factionMap.contains(faction2))
		return false;

	Faction* faction = factionMap.getFaction(faction1);

	return faction->getEnemies()->contains(faction2);
}

bool FactionManager::isAlly(const String& faction1, const String& faction2) {

	if (!factionMap.contains(faction1) || !factionMap.contains(faction2))
		return false;

	Faction* faction = factionMap.getFaction(faction1);

	return faction->getAllies()->contains(faction2);
}
