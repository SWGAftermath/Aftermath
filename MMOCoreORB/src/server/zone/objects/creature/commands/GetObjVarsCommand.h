/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETOBJVARSCOMMAND_H_
#define GETOBJVARSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/creature/ai/CreatureTemplate.h"

class GetObjVarsCommand : public QueueCommand {
public:

	GetObjVarsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		uint64 objectID = 0;
		//UnicodeTokenizer tokenizer(arguments);
        //tokenizer.setDelimeter(" ");
        StringTokenizer args(arguments.toString());
		

		// if we have an argument passed, use it
		if (args.hasMoreTokens()) {
            String commandType;
            args.getStringToken(commandType);
            
            if (commandType.beginsWith("spout")) {
                if (target == 0){
                    creature->sendSystemMessage("You must target an object for /getObjVars spout to function.");
                    return INVALIDPARAMETERS;
                }

                objectID = target;
                ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(objectID, false);
                
                String planetName = object->getZone()->getZoneName();
                String templateFile = object->getObjectTemplate()->getFullTemplateString();
                StringBuffer text;
                
                if (templateFile.contains("object/mobile")){
                    int angle = object->getDirectionAngle();
                    
                    // Beause they crash the server if we try to use them as an AI agent.
                    if (templateFile.contains("junk") || templateFile.contains("vehicle") || templateFile.contains("vendor")){ 
                       creature->sendSystemMessage("Sorry, this feature does not support the selected object or NPC.");
                       return INVALIDPARAMETERS;
                    }
                    
                    AiAgent* mob = object.castTo<AiAgent*> ();
                    CreatureTemplate* creatureTemplate = mob->getCreatureTemplate();
                    String mobileName = creatureTemplate->getTemplateName();

                    text << "spawnMobile(\"" << planetName << "\", " <<  "\"" << mobileName << "\", 1, ";
                
                    if (object->getParent() != NULL && object->getParent().get()->isCellObject()) {
                        // Inside
                        ManagedReference<CellObject*> cell = cast<CellObject*>( object->getParent().get().get());
                        Vector3 cellPosition = object->getPosition();

                        text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << angle << ", " << cell->getObjectID() << ")";
                    }else {
                        // Outside
                        Vector3 worldPosition = object->getWorldPosition();
                        
                        text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << angle << ", " << "0" << ")\n";
                    }
                    
                    creature->sendSystemMessage(text.toString());// spawnMobile("planet", "mobileTemplate", respawnTimer, x, z, y, heading, cellid)
                } else {
                    text << "spawnSceneObject(\"" << planetName << "\", \"" << templateFile << "\", ";
                
                    if (object->getParent() != NULL && object->getParent().get()->isCellObject()) {
                        // Inside
                        ManagedReference<CellObject*> cell = cast<CellObject*>( object->getParent().get().get());
                        Vector3 cellPosition = object->getPosition();

                        text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << cell->getObjectID() << ", ";
                    }else {
                        // Outside
                        Vector3 worldPosition = object->getWorldPosition();
                        text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << "0" << ", ";
                    }
                    
                    Quaternion* dir = object->getDirection();
                    
                    text << dir->getW() << ", " << dir->getX() << ", " << dir->getY() << ", " << dir->getZ() << ")\n";
                    
                    creature->sendSystemMessage(text.toString()); // spawnSceneObject("planet", "objectTemplateFilePathAndName", x, z, y, cellNumber, dw, dx, dy, dz> 
                }
                
                return SUCCESS;
            } 
            else if (commandType.beginsWith("static")){ // Having this seperate function allows you to still use /getObjVars spout if you want to use the tangible object version instead.
                if (target == 0){
                    creature->sendSystemMessage("You must target an object for /getObjVars static to function.");
                    return INVALIDPARAMETERS;
                }
                
                objectID = target;
                ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(objectID, false);
                
                String planetName = object->getZone()->getZoneName();
                String templateFile = object->getObjectTemplate()->getFullTemplateString();
                
                if (!templateFile.contains("furniture/static")){
                    creature->sendSystemMessage("Incorrect Usage: Target object must be a decendant of object/tangible/furniture/static/");
                    creature->sendSystemMessage("These items are available on a special character builder style terminal.");
                    creature->sendSystemMessage("/object createitem object/tangible/beta/donham_terminal.iff");
                    return INVALIDPARAMETERS;
                }
                
                templateFile = templateFile.replaceAll("tangible/furniture/", ""); // Convert from Admin-handy tangible version to the normal static version.
                
                 if (templateFile.contains("static/building"))
                    templateFile = templateFile.replaceAll("static/building", "building"); // Fix path for filler type buildings
                
                StringBuffer text;
                
                text << "spawnSceneObject(\"" << planetName << "\", \"" << templateFile << "\", ";
                
                if (object->getParent() != NULL && object->getParent().get()->isCellObject()) {
                    // Inside
                    ManagedReference<CellObject*> cell = cast<CellObject*>( object->getParent().get().get());
                    Vector3 cellPosition = object->getPosition();

                    text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << cell->getObjectID() << ", ";
                }else {
                    // Outside
                    Vector3 worldPosition = object->getWorldPosition();
                    text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << "0" << ", ";
                }
                
                Quaternion* dir = object->getDirection();
                
                text << dir->getW() << ", " << dir->getX() << ", " << dir->getY() << ", " << dir->getZ() << ")\n";
                
                creature->sendSystemMessage(text.toString()); // spawnSceneObject("planet", "staticObjectTemplateFilePathAndName", x, z, y, cellNumber, dw, dx, dy, dz> 
                return SUCCESS;
            } 
            else if (commandType.beginsWith("onme")){
                //PlayerObject* targetGhost = creature->getPlayerObject();
                
                String planetName = creature->getZone()->getZoneName();
                int angle = creature->getDirectionAngle();
                
                StringBuffer text;
                
                text << "spawnMobile(\"" << planetName << "\", " <<  "\"commoner" << "\", 1, ";
                
                if (creature->getParent() != NULL && creature->getParent().get()->isCellObject()) {
                    // Inside
                    ManagedReference<CellObject*> cell = cast<CellObject*>( creature->getParent().get().get());
                    Vector3 cellPosition = creature->getPosition();

                    text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << angle << ", " << cell->getObjectID() << ")";
                }else {
                    // Outside
                    Vector3 worldPosition = creature->getWorldPosition();
                    
                    text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << angle << ", " << "0" << ")\n";
                }
                
                creature->sendSystemMessage(text.toString());// spawnMobile("planet", "mobileTemplate", respawnTimer, x, z, y, heading, cellid)
                return SUCCESS;
            } 
            else if (commandType.beginsWith("id")){
                try {
                    objectID = args.getLongToken();
                } catch ( Exception& err ) {
                    creature->sendSystemMessage("INVALID OBJECT.  Please specify a valid object name or objectID");
                    return INVALIDPARAMETERS;
                }
            }
            else if (commandType.beginsWith("myparent")){
                if (creature->getParent() != NULL && creature->getParent().get()->isCellObject()) {
                    ManagedReference<CellObject*> cell = cast<CellObject*>( creature->getParent().get().get());
                    ManagedReference<SceneObject*> parent = cell->getParent().get();
                    creature->sendSystemMessage("Parent Structure ID: " + String::valueOf(parent->getObjectID()));
                } else {
                    creature->sendSystemMessage("/getObjVars myparent is only useful when you're inside a structure.");
                }
                return SUCCESS;
            }
		} else {
			objectID = target;
		}

		if ( objectID == 0 ) {
			creature->sendSystemMessage("You need to target an object or specify an object id: /getobjvars <objectID> ");
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(objectID, false);

		if ( object == NULL) {
			creature->sendSystemMessage("ERROR GETTIGN OBJECT - NULL " + String::valueOf(objectID));
		} else {

			String strClassName = object->getObjectNameStringIdName();
			String strDescription = object->getDetailedDescription();
			bool bMarkedForDelete = object->_isMarkedForDeletion();
			bool bIsUpdated = object->_isUpdated();
			int rCount = object.get()->getReferenceCount();
			uint64 parentID = object->getParentID();
			StringBuffer msg;
			msg << endl << "OBJECTID: " << String::valueOf(objectID) << endl;
			msg << "OBJECTTYPE: " << String::valueOf(object->getGameObjectType()) << endl;

			if(object->isCreatureObject()) {
				msg << "Creature First Name: " << object.castTo<CreatureObject*>()->getFirstName() << endl;
			}

			msg << "CLASS: " << strClassName << endl;
			msg << "Marked for deletion: " << String::valueOf(bMarkedForDelete) << endl;
			msg << "IsUpdated: " <<  String::valueOf(bIsUpdated) << endl;
			msg << "REFERENCE COUNT " << String::valueOf(rCount) << endl;
			msg << "Path: " << object->getObjectTemplate()->getFullTemplateString() << endl;
			msg << "Children: " << String::valueOf(object->getChildObjects()->size()) << endl;
			msg << "PARENT OBJECTID: " << String::valueOf(parentID) << endl;

			if(object->getZone() != NULL)
				msg << "location: " << String::valueOf(object->getPositionX()) << " "  << String::valueOf(object->getPositionY()) << " " << object->getZone()->getZoneName() << endl;

			ManagedReference<CityRegion*> city = object->getCityRegion().get();
			if (city != NULL)
				msg << "City Region oid: " << String::valueOf(city->getObjectID()) << ", name: " << city->getRegionDisplayedName() << endl;

			creature->sendSystemMessage(msg.toString());

			ChatManager* chatManager = server->getZoneServer()->getChatManager();
			String title = "getObjVars - " + String::valueOf(objectID);
			chatManager->sendMail("System", title , msg.toString(), creature->getFirstName());
		}


		return SUCCESS;
	}

};

#endif //GETOBJVARSCOMMAND_H_