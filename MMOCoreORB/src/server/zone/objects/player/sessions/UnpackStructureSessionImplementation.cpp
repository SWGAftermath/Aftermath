/*
 * UnpackStructureSessionImplementation.cpp
 */

#include "server/chat/ChatManager.h"
#include "server/zone/objects/player/sessions/UnpackStructureSession.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/structure/tasks/StructureConstructionCompleteTask.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/StructureControlDevice.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/Zone.h"

int UnpackStructureSessionImplementation::constructStructure(float x, float y, int angle) {
	ManagedReference<StructureObject*> structure = structureObject.get();
	ManagedReference<Zone*> thisZone = zone.get();
	ManagedReference<CreatureObject*> creature = creatureObject.get();

	if (structure == nullptr || thisZone == nullptr || creature == nullptr)
		return cancelSession();

	positionX = x;
	positionY = y;
	directionAngle = angle;

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = structure->getObjectTemplate()->getFullTemplateString();
	Reference<const SharedStructureObjectTemplate*> serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	if (serverTemplate == nullptr || temporaryNoBuildZone.get() != nullptr)
		return cancelSession(); //Something happened, the server template is not a structure template or temporaryNoBuildZone already set.

	placeTemporaryNoBuildZone(serverTemplate);

	String barricadeServerTemplatePath = serverTemplate->getConstructionMarkerTemplate();
	int constructionDuration = 100; //Set the duration for 100ms as a fall back if it doesn't have a barricade template.

	if (!barricadeServerTemplatePath.isEmpty()) {
		ManagedReference<SceneObject*> barricade = ObjectManager::instance()->createObject(barricadeServerTemplatePath.hashCode(), 0, "");

		if (barricade != nullptr) {
			barricade->initializePosition(x, 0, y); //The construction barricades are always at the terrain height.

			const StructureFootprint* structureFootprint = serverTemplate->getStructureFootprint();

			if (structureFootprint != nullptr && (structureFootprint->getRowSize() > structureFootprint->getColSize())) {
				angle = angle + 180;
			}

			barricade->rotate(angle); //All construction barricades need to be rotated 180 degrees for some reason.

			Locker tLocker(barricade);

			thisZone->transferObject(barricade, -1, true);

			constructionDuration = serverTemplate->getLotSize() * 3000; //3 seconds per lot.

			constructionBarricade = barricade;
		}
	}

	Reference<Task*> task = new StructureConstructionCompleteTask(creature, true);
	task->schedule(constructionDuration);

	return 0;
}

void UnpackStructureSessionImplementation::placeTemporaryNoBuildZone(const SharedStructureObjectTemplate* serverTemplate) {
	ManagedReference<Zone*> thisZone = zone.get();

	if (thisZone == nullptr)
		return;

	Reference<const StructureFootprint*> structureFootprint = serverTemplate->getStructureFootprint();
	ManagedReference<CircularAreaShape*> areaShape = new CircularAreaShape();

	Locker alocker(areaShape);

	// Guild halls are approximately 55 m long, 64 m radius will surely cover that in all directions.
	// Even if the placement coordinate aren't in the center of the building.
	areaShape->setRadius(64);
	areaShape->setAreaCenter(positionX, positionY);

	ManagedReference<ActiveArea*> noBuildZone = (thisZone->getZoneServer()->createObject(STRING_HASHCODE("object/active_area.iff"), 0)).castTo<ActiveArea*>();

	Locker locker(noBuildZone);

	noBuildZone->initializePosition(positionX, 0, positionY);
	noBuildZone->setAreaShape(areaShape);
	noBuildZone->setNoBuildArea(true);

	thisZone->transferObject(noBuildZone, -1, true);

	temporaryNoBuildZone = noBuildZone;
}

void UnpackStructureSessionImplementation::removeTemporaryNoBuildZone() {
	ManagedReference<ActiveArea*> noBuildZone = temporaryNoBuildZone.get();

	if (noBuildZone != nullptr) {
		Locker locker(noBuildZone);

		noBuildZone->destroyObjectFromWorld(true);
	}
}

int UnpackStructureSessionImplementation::completeSession() {
	ManagedReference<SceneObject*> barricade = constructionBarricade.get();

	if (barricade != nullptr) {
		Locker locker(barricade);

		barricade->destroyObjectFromWorld(true);
	}

	ManagedReference<StructureObject*> structure = structureObject.get();
	ManagedReference<CreatureObject*> creature = creatureObject.get();
	ManagedReference<Zone*> thisZone = zone.get();

	if (structure == nullptr || creature == nullptr || thisZone == nullptr)
		return cancelSession();

	ManagedReference<StructureControlDevice*> controlDevice = structure->getControlDevice().get().castTo<StructureControlDevice*>();

	if (controlDevice == nullptr)
		return cancelSession();

	bool structureUnpacked = StructureManager::instance()->unpackStructure(creature, structure, positionX, positionY, directionAngle);

	if (!structureUnpacked)
		return cancelSession();

	removeTemporaryNoBuildZone();

	Locker clocker(structure, creature);
	controlDevice->notifyStructurePlaced(creature, structure);

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != nullptr) {
		//Create Waypoint
		ManagedReference<WaypointObject*> waypointObject = ( thisZone->getZoneServer()->createObject(STRING_HASHCODE("object/waypoint/world_waypoint_blue.iff"), 1)).castTo<WaypointObject*>();

		Locker locker(waypointObject);

		waypointObject->setCustomObjectName(structure->getDisplayedName(), false);
		waypointObject->setActive(true);
		waypointObject->setPosition(positionX, 0, positionY);
		waypointObject->setPlanetCRC(thisZone->getZoneCRC());
		structure->setWaypointID(waypointObject->getObjectID());

		ghost->addWaypoint(waypointObject, false, true);

		locker.release();

		//Create an email.
		ManagedReference<ChatManager*> chatManager = thisZone->getZoneServer()->getChatManager();

		if (chatManager != nullptr) {
			UnicodeString subject = "@player_structure:construction_complete_subject";

			StringIdChatParameter emailBody("@player_structure:construction_complete");
			emailBody.setTO(structure->getObjectName());
			emailBody.setDI(ghost->getLotsRemaining());

			chatManager->sendMail("@player_structure:construction_complete_sender", subject, emailBody, creature->getFirstName(), waypointObject);
		}

		if (structure->isBuildingObject()) {
			BuildingObject* building = cast<BuildingObject*>(structure.get());

			if (building->getSignObject() != nullptr)
				building->setCustomObjectName(building->getCustomObjectName(), true);
		}
	}

	return cancelSession(); //Canceling the session just removes the session from the player's map.
}
