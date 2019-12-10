/*
 * PackupStructureCodeSuiCallback.h
 */

#ifndef PACKUPSTRUCTURECODESUICALLBACK_H_
#define PACKUPSTRUCTURECODESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/PackupStructureSession.h"


class PackupStructureCodeSuiCallback : public SuiCallback {
public:
	PackupStructureCodeSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<PackupStructureSession*> session = player->getActiveSession(SessionFacadeType::PACKUPSTRUCTURE).castTo<PackupStructureSession*>();

		if (session == nullptr)
			return;

		if (cancelPressed) {
			session->cancelSession();
			return;
		}

		uint32 inputtedCode = Integer::valueOf(args->get(0).toString());

		if (!session->isPackupCode(inputtedCode)) {
			player->sendSystemMessage("@player_structure:incorrect_packup_code"); //You have entered an incorrect code. You will have to issue the /packupStructure again if you wish to continue.
			session->cancelSession();
			return;
		}

		session->packupStructure();
	}
};

#endif /* PACKUPSTRUCTURECODESUICALLBACK_H_ */
