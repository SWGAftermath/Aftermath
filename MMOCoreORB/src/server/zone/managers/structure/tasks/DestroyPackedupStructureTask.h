/*
 * DestroyPackedupStructureTask.h
 */

#ifndef DESTROYPACKEDUPSTRUCTURETASK_H_
#define DESTROYPACKEDUPSTRUCTURETASK_H_

#include "server/zone/Zone.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/objects/intangible/StructureControlDevice.h"

class DestroyPackedupStructureTask : public Task {
protected:
	ManagedReference<StructureObject*> structureObject;

public:
	DestroyPackedupStructureTask(StructureObject* structure) {
		structureObject = structure;
		setCustomTaskQueue("slowQueue");
	}

	void run() {
		Locker locker(structureObject);

		ZoneServer* zoneServer = structureObject->getZoneServer();

		if (zoneServer != nullptr && zoneServer->isServerLoading()) {
			schedule(1000);
			return;
		}

		//Get the owner of the structure, and remove the structure from their possession.
		ManagedReference<SceneObject*> owner = zoneServer->getObject(structureObject->getOwnerObjectID());

		if (owner != nullptr) {
			ManagedReference<SceneObject*> ghost = owner->getSlottedObject("ghost");

			if (ghost != nullptr && ghost->isPlayerObject()) {
				PlayerObject* playerObject = cast<PlayerObject*>(ghost.get());
				playerObject->removeOwnedStructure(structureObject);

				uint64 waypointID = structureObject->getWaypointID();

				if (waypointID != 0)
					playerObject->removeWaypoint(waypointID, true, true);
			}
		}

		ManagedReference<StructureControlDevice*> controlDevice = structureObject->getControlDevice().get().castTo<StructureControlDevice*>();
		if (controlDevice != nullptr) {
			controlDevice->destroyObjectFromWorld(true);
			controlDevice->destroyObjectFromDatabase(true);
		}

		structureObject->destroyObjectFromDatabase(true);
		structureObject->destroyObjectFromWorld(true);
		structureObject->notifyObservers(ObserverEventType::OBJECTDESTRUCTION, structureObject, 0);
	}
};

#endif /* DESTROYPACKEDUPSTRUCTURETASK_H_ */
