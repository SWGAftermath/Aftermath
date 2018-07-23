//PLAYER

#ifndef PLAYER_BH_SUI_CALLBACK
#define PLAYER_BH_SUI_CALLBACK

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/visibility/VisibilityManager.h"
#include "server/zone/objects/player/sui/callbacks/BountyHuntSuiCallback.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/managers/mission/MissionManager.h"

class BountyHuntSuiCallback : public SuiCallback {

public:
	BountyHuntSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

void run(CreatureObject* creature, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (creature == NULL || cancelPressed) {
			return;
		}

		try
		{
			//int value = Integer::valueOf(args->get(0).toString());

			int value = 50000;

			ManagedReference<SceneObject*> suiObject = suiBox->getUsingObject();
			CreatureObject* player = cast<CreatureObject*>(suiObject.get());
			if (creature->getBankCredits() + creature->getCashCredits() >= value) {
				VisibilityManager::instance()->clearVisibility(player);
				if (creature->getBankCredits() > value) {
					creature->subtractBankCredits(value);
				} else {
					creature->subtractCashCredits(value - creature->getBankCredits());
					creature->subtractBankCredits(creature->getBankCredits());
				}
				int bountyWorth = player->getScreenPlayState("deathBounty") + 1;
				player->setScreenPlayState("deathBounty", bountyWorth);
				player->playEffect("clienteffect/ui_missile_aquiring.cef", "");
				creature->playEffect("clienteffect/holoemote_haunted.cef", "head");
				creature->sendSystemMessage("Bounty has been successfully placed!");
				VisibilityManager::instance()->increaseVisibility(player, 8000); // Max vis
				uint64 id = player->getObjectID();
				MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
				PlayerObject* ghost = player->getPlayerObject();
				missionManager->updatePlayerBountyReward(id, ghost->calculateBhReward());

			}
			else creature->sendSystemMessage("You have insufficient funds!");
		} catch(Exception& e) { }
	}
};

#endif