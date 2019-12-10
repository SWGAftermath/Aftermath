/*
 * UnpackStructureComponent.cpp
 */

#include "UnpackStructureComponent.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/intangible/StructureControlDevice.h"
#include "server/zone/Zone.h"

int UnpackStructureComponent::placeStructure(CreatureObject* creature, StructureObject* structureObject, float x, float y, int angle) const {
	Zone* zone = creature->getZone();

	if (zone != nullptr)
		StructureManager::instance()->unpackStructureFromControlDevice(creature, structureObject, x, y, angle);

	return 0;
}

int UnpackStructureComponent::notifyStructurePlaced(CreatureObject* creature, StructureObject* structureObject) const {
	ManagedReference<StructureControlDevice*> controlDevice = structureObject->getControlDevice().get().castTo<StructureControlDevice*>();

	if (controlDevice != nullptr) {
		controlDevice->destroyObjectFromWorld(true);
		controlDevice->destroyObjectFromDatabase(true);
	}

	structureObject->setControlDevice(nullptr);

	return 0;
}
