/*
 * PackupStructureRequestSuiCallback.h
 */

#ifndef PACKUPSTRUCTUREREQUESTSUICALLBACK_H_
#define PACKUPSTRUCTUREREQUESTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/PackupStructureSession.h"

class PackupStructureRequestSuiCallback : public SuiCallback {
public:
	PackupStructureRequestSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
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

		session->sendPackupCode();
	}
};

#endif /* PACKUPSTRUCTUREREQUESTSUICALLBACK_H_ */
