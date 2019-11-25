/*
 * StructureConstructionCompleteTask.h
 *
 *  Created on: Jun 13, 2011
 *      Author: crush
 */


#ifndef STRUCTURECONSTRUCTIONCOMPLETETASK_H_
#define STRUCTURECONSTRUCTIONCOMPLETETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/PlaceStructureSession.h"
#include "server/zone/objects/player/sessions/UnpackStructureSession.h"

class StructureConstructionCompleteTask : public Task {
	ManagedWeakReference<CreatureObject*> creatureObject;
	bool isStructureUnpack;

public:
	StructureConstructionCompleteTask(CreatureObject* creature, bool unpackStructure) : Task() {
		creatureObject = creature;
		isStructureUnpack = unpackStructure;
	}

	void run() {
		ManagedReference<CreatureObject*> creature = creatureObject.get();
		bool unpackStructure = isStructureUnpack;

		if (creature == nullptr)
			return;

		Locker lock(creature);

		if (unpackStructure) {
			ManagedReference<UnpackStructureSession*> session = creature->getActiveSession(SessionFacadeType::UNPACKSTRUCTURE).castTo<UnpackStructureSession*>();

			if (session != nullptr)
				session->completeSession();
		} else {
			ManagedReference<PlaceStructureSession*> session = creature->getActiveSession(SessionFacadeType::PLACESTRUCTURE).castTo<PlaceStructureSession*>();

			if (session != nullptr)
				session->completeSession();
		}
	}
};

#endif /*STRUCTURECONSTRUCTIONCOMPLETETASK_H_*/
