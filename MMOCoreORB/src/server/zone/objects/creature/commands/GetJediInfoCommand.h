/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETJEDIINFOCOMMAND_H_
#define GETJEDIINFOCOMMAND_H_

class GetJediInfoCommand : public QueueCommand {
public:

	GetJediInfoCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		String syntaxerror = "Invalid arguments: /getJediInfo <firstname>";

		ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);

		ManagedReference<CreatureObject* > targetPlayer = NULL;
		CreatureObject* player = cast<CreatureObject*>(creature);
		StringTokenizer args(arguments.toString());

		if (object == NULL || !object->isPlayerCreature()) {

			String firstName;
			if (args.hasMoreTokens()) {
				args.getStringToken(firstName);
				targetPlayer = server->getZoneServer()->getPlayerManager()->getPlayer(firstName);
			}

		} else {
			targetPlayer = cast<CreatureObject*>( object.get());
		}

		if (targetPlayer == NULL) {
			player->sendSystemMessage(syntaxerror);
			return INVALIDPARAMETERS;
		}

		ManagedReference<PlayerObject*> targetGhost = targetPlayer->getPlayerObject();

		if (targetGhost == NULL) {
			player->sendSystemMessage(syntaxerror);
			return INVALIDPARAMETERS;
		}

		try {

			Locker playerlocker(targetPlayer);
			// Send message with current character age
			int toonAge = targetGhost->getCharacterAgeInDays();
			int jediTime = targetGhost->getJediTime();
			int daysLeft = jediTime - toonAge;

			player->sendSystemMessage(targetPlayer->getFirstName() + " is currently " + toonAge + " days old and has a jedi unlock time of " + jediTime + " days. " + daysLeft + " until unlock");

		} catch (Exception& e) {
			player->sendSystemMessage(syntaxerror);
		}


		return SUCCESS;
	}

};

#endif //GETJEDIINFOCOMMAND_H_