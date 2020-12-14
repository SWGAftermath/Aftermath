/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GUILDSTATUSCOMMAND_H_
#define GUILDSTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

class GuildstatusCommand : public QueueCommand {
public:

	GuildstatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);

		ZoneServer* zoneServer = server->getZoneServer();

		ManagedReference<SceneObject*> obj = nullptr;

		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		if (tokenizer.hasMoreTokens()) {
			ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
			
			UnicodeString arg;
			tokenizer.getUnicodeToken(arg);
			
			if (arg == "list") {
				if (!player->isInGuild()) {
					player->sendSystemMessage("You are not in a guild.");
					return GENERALERROR;
				}

				ManagedReference<GuildObject*> guild = player->getGuildObject().get();
				uint64 objid = player->getObjectID();

				if (guild == nullptr)
					return GENERALERROR;

				if (!guild->hasMember(objid))
					return GENERALERROR;
				
				Vector<uint64> members;
				
				Locker locker(guild);

				GuildMemberList* memberList = guild->getGuildMemberList();

				if (memberList == nullptr)
					return GENERALERROR;

				for (int i = 0; i < memberList->size(); ++i) {
					GuildMemberInfo* gmi = &memberList->get(i);

					if (gmi == nullptr)
						continue;

					members.add(gmi->getPlayerID());
				}

				locker.release();
				
				StringBuffer msg;
				StringBuffer prompt;
				
				if (tokenizer.hasMoreTokens()) {
					UnicodeString arg;
					tokenizer.getUnicodeToken(arg);
					
					if (arg == "-online") {
						prompt << "Guild Member List (online only)";
						
						for (const auto& memberID : members) {
							auto firstName = guild->getZoneServer()->getPlayerManager()->getPlayerName(memberID);
							obj = zoneServer->getObject(memberID);
							CreatureObject* gmember = cast<CreatureObject*>(obj.get());

							if (gmember->isOnline()) {
								msg << "\\#ffd300" << firstName << " - online\n";
							}
						}
						//msg << "\\#ffffff--------------\nEnd of Guild List.";
					} else {
						player->sendSystemMessage("SYNTAX: /guildStatus list");
						player->sendSystemMessage("SYNTAX: /guildStatus list -online");
						return INVALIDPARAMETERS;
					}
				} else {
					prompt << "Guild Member List";
					
					for (const auto& memberID : members) {
						auto firstName = guild->getZoneServer()->getPlayerManager()->getPlayerName(memberID);
						obj = zoneServer->getObject(memberID);
						CreatureObject* gmember = cast<CreatureObject*>(obj.get());

						if (gmember->isOnline()) {
							msg << "\\#ffd300" << firstName << " - online";
						} else {
							msg << firstName;
						}

						msg << "\\#ffffff\n";
					}
					//msg << "\\#ffffff--------------\nEnd of Guild List.";
				}
				
				ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

				if (ghost == nullptr) {
					return GENERALERROR;
				}
				ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::NONE);
				box->setPromptTitle(prompt.toString());
				box->setPromptText(msg.toString());

				ghost->addSuiBox(box);
				player->sendMessage(box->generateMessage());
				//player->sendSystemMessage(msg.toString());
				return SUCCESS;
			} else if (arg == "help") {
				player->sendSystemMessage("SYNTAX: /guildStatus list");
				player->sendSystemMessage("SYNTAX: /guildStatus list -online");
				return SUCCESS;
			} else {
				uint64 targetPlayerID = playerManager->getObjectID(arg.toString());

				obj = zoneServer->getObject(targetPlayerID);
			}
		}

		if (obj == nullptr || !obj->isCreatureObject())
			obj = zoneServer->getObject(target);

		if (obj == nullptr || !obj->isPlayerCreature()) {
			player->sendSystemMessage("@base_player:guildstatus_not_player"); //You may only check the guild status of players.
			return GENERALERROR;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>( obj.get());

		StringIdChatParameter params;
		params.setTU(targetCreature->getDisplayedName());

		if (!targetCreature->isInGuild()) {
			params.setStringId("@base_player:guildstatus_not_in_guild"); //%TU is not in a guild.
			player->sendSystemMessage(params);
			return GENERALERROR;
		}

		ManagedReference<GuildObject*> tarGuild = targetCreature->getGuildObject().get();
		uint64 tarObjid = targetCreature->getObjectID();

		if (tarGuild == nullptr)
			return GENERALERROR;

		if (!tarGuild->hasMember(tarObjid))
			return GENERALERROR;

		String tarGuildTitle = tarGuild->getGuildMemberTitle(tarObjid);
		params.setTT(tarGuild->getGuildName());

		StringBuffer stringid;
		stringid << "@base_player:guildstatus_";

		if (tarGuild->getGuildLeaderID() == tarObjid)
			stringid << "leader";
		else
			stringid << "member";

		if (!tarGuildTitle.isEmpty()) {
			stringid << "_title";
			params.setTO(tarGuildTitle);
		}

		params.setStringId(stringid.toString());
		player->sendSystemMessage(params);

		return SUCCESS;
	}

};

#endif //GUILDSTATUSCOMMAND_H_
