/*
 * StructureControlDeviceImplementation.cpp
 */
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/components/UnpackStructureComponent.h"
#include "server/zone/objects/intangible/StructureControlDevice.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/player/EnterStructurePlacementModeMessage.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "templates/manager/TemplateManager.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/ZoneServer.h"

void StructureControlDeviceImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
		menuResponse->addRadialMenuItem(18, 3, "@player_structure:management_status"); //Status
		menuResponse->addRadialMenuItem(19, 3, "@player_structure:management_pay"); //Pay Maintenance
		menuResponse->addRadialMenuItem(20, 3, "@player_structure:structure_unpack"); // Unpack Structure
		return;
}

int StructureControlDeviceImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	ManagedReference<StructureObject*> structure = this->controlledObject.get().castTo<StructureObject*>();
	if (structure == nullptr)
		return 0;

	if (!isASubChildOf(player))
		return 0;

	switch (selectedID) {
	case 18: {
		player->executeObjectControllerAction(0x13F7E585, structure->getObjectID(), ""); //structureStatus
		return 0;
	}

	case 19: {
		player->executeObjectControllerAction(0xE7E35B30, structure->getObjectID(), ""); //payMaintenance
		return 0;
	}

	case 20: {
		placeStructureMode(player, structure);
		return 0;
	}

	default:
		return 0;
	};

	return 0;
}

void StructureControlDeviceImplementation::placeStructureMode(CreatureObject* player, StructureObject* structure) {
	if (player->isRidingMount()) {
		player->sendSystemMessage("@player_structure:cant_place_mounted");
		return;
	}

	if (player->getParent() != nullptr) {
		player->sendSystemMessage("@player_structure:not_inside"); //You can not place a structure while you are inside a building.
		return;
	}

	ManagedReference<CityRegion*> city = player->getCityRegion().get();

	if (city != nullptr && city->isClientRegion()) {
		player->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
		return;
	}

	TemplateManager* templateManager = TemplateManager::instance();

	String serverTemplatePath = structure->getObjectTemplate()->getFullTemplateString();
	Reference<SharedStructureObjectTemplate*> serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

	if (serverTemplate == nullptr)
		return;

	String clientTemplatePath = templateManager->getTemplateFile(serverTemplate->getClientObjectCRC());

	EnterStructurePlacementModeMessage* espmm = new EnterStructurePlacementModeMessage(this->getObjectID(), clientTemplatePath);
	player->sendMessage(espmm);
}

int StructureControlDeviceImplementation::placeStructure(CreatureObject* player, float x, float y, int angle) {
	ManagedReference<StructureObject*> structure = this->controlledObject.get().castTo<StructureObject*>();
	if (structure == nullptr)
		return 1;

	Reference<UnpackStructureComponent*> component = new UnpackStructureComponent();

	if (component != nullptr)
		component->placeStructure(player, structure, x, y, angle);

	return 1;
}

int StructureControlDeviceImplementation::notifyStructurePlaced(CreatureObject* player, StructureObject* structure) {
	Reference<UnpackStructureComponent*> component = new UnpackStructureComponent();

	if (component != nullptr)
		component->notifyStructurePlaced(player, structure);

	return 1;
}

void StructureControlDeviceImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

	ManagedReference<StructureObject*> structure = this->controlledObject.get().castTo<StructureObject*>();
	if (structure == nullptr)
		return;

	TemplateManager* templateManager = TemplateManager::instance();

	uint32 structureCRC = structure->getObjectTemplate()->getFullTemplateString().hashCode();

	SharedStructureObjectTemplate* structureTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(structureCRC));

	if (structureTemplate == nullptr)
		return;

	for (int i = 0; i < structureTemplate->getTotalAllowedZones(); ++i) {
		String zoneName = structureTemplate->getAllowedZone(i);

		if (zoneName.isEmpty())
			continue;

		alm->insertAttribute("examine_scene", "@planet_n:" + zoneName); //Can Be Built On
	}
}
