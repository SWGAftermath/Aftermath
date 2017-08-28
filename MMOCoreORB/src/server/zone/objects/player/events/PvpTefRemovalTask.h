
#ifndef PVPTEFREMOVALTASK_H_
#define PVPTEFREMOVALTASK_H_

#include "server/zone/objects/player/PlayerObject.h"
#include "templates/params/creature/CreatureFlag.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PvpTefRemovalTask: public Task {
	ManagedWeakReference<CreatureObject*> creature;

public:
	PvpTefRemovalTask(CreatureObject* creo) {
		creature = creo;
	}

	void run() {
		ManagedReference<CreatureObject*> player = creature.get();

		if (player == NULL)
			return;

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject().get();

		if (ghost == NULL) {
			return;
		}

		Locker locker(player);

		if (ghost->hasPvpTef()) {
			auto gcwTefMs = ghost->getLastGcwPvpCombatActionTimestamp().miliDifference();
			auto bhTefMs = ghost->getLastBhPvpCombatActionTimestamp().miliDifference();
			auto jediTefMs = ghost->getLastJediPvpCombatActionTimestamp().miliDifference();
			if (jediTefMs < 0){
				this->reschedule(llabs(jediTefMs));
			}else{
				this->reschedule(llabs(jediTefMs < gcwTefMs ? (jediTefMs < bhTefMs ? jediTefMs : bhTefMs) : (gcwTefMs < bhTefMs ? gcwTefMs : bhTefMs )));
			}
		} else {
			ghost->updateInRangeBuildingPermissions();
			player->clearPvpStatusBit(CreatureFlag::TEF);
		}

		if (!ghost->hasBhTef())
			player->notifyObservers(ObserverEventType::BHTEFCHANGED);
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* PVPTEFREMOVALTASK_H_ */
