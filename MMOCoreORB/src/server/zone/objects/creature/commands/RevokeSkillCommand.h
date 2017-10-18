/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REVOKESKILLCOMMAND_H_
#define REVOKESKILLCOMMAND_H_

class RevokeSkillCommand : public QueueCommand {
public:

	RevokeSkillCommand(const String& name, ZoneProcessServer* server)
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

		SkillManager* skillManager = SkillManager::instance();
		bool skillRevoked = skillManager->surrenderSkill(arguments.toString(), targetCreature, true);

		if (skillRevoked) {
			StringIdChatParameter params;
			params.setTO(arguments.toString());
			params.setStringId("skill_teacher", "skill_terminal_grant");

			targetCreature->sendSystemMessage(params);

			creature->sendSystemMessage("Revoked skill " + arguments.toString()
					+ "to " + targetCreature->getFirstName());
		} else {
			StringIdChatParameter params;
			params.setTO(arguments.toString());
			params.setStringId("skill_teacher", "prose_train_failed");

			targetCreature->sendSystemMessage(params);

			creature->sendSystemMessage("Failed to revoke skill " + arguments.toString()
					+ "to " + targetCreature->getFirstName());
		}

		return SUCCESS;
	}

};

#endif //REVOKESKILLCOMMAND_H_
