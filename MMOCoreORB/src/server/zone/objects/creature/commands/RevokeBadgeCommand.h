/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REVOKEBADGECOMMAND_H_
#define REVOKEBADGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RevokeBadgeCommand : public QueueCommand {
public:

	RevokeBadgeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
		UnicodeTokenizer tokenizer(arguments);

		if (!tokenizer.hasMoreTokens()) {
			creature->sendSystemMessage("Syntax: /revokeBadge [badge id]");
			return GENERALERROR;
		}

		if (targetObject == nullptr || !targetObject->isPlayerCreature()) {
			creature->sendSystemMessage("Error: You must have a player targeted to use this command.");
			return INVALIDTARGET;
		}

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(targetObject.get());

		if (player != nullptr) {
			PlayerObject* ghost = player->getPlayerObject();
			int badgeId = tokenizer.getIntToken();

			if (ghost != nullptr) {
				if (ghost->hasBadge(badgeId)) {
					ghost->unsetBadge(badgeId);
					creature->sendSystemMessage("You have removed badge id: " + String::valueOf(badgeId) + " from your target.");
				} else {
					creature->sendSystemMessage("Error: Player does not have the specified badge.");
				}
			}
		}
		return SUCCESS;
	}
};

#endif //REVOKEBADGECOMMAND_H_