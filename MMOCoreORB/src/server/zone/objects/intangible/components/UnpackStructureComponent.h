/*
 * UnpackStructureComponent.h
 *
 */

#ifndef UNPACKSTRUCTURECOMPONENT_H_
#define UNPACKSTRUCTURECOMPONENT_H_

#include "server/zone/objects/scene/components/SceneObjectComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
namespace structure {
	class StructureObject;
}
}
}
}

using namespace server::zone::objects::creature;
using namespace server::zone::objects::structure;

class UnpackStructureComponent : public SceneObjectComponent {
public:
	virtual int placeStructure(CreatureObject* creature, StructureObject* structure, float x, float y, int angle) const;
	virtual int notifyStructurePlaced(CreatureObject* creature, StructureObject* structure) const;
};


#endif /* UNPACKSTRUCTURECOMPONENT_H_*/
