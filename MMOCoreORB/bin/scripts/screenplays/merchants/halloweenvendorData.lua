HalloweenEventVendorLogic = VendorLogic:new {
	scriptName = "HalloweenEventVendorLogic",
	currencies = {
	--For Tokens: Displayed Name, full template string (without shared_), if applicable: ScreenPlayData string, ScreenPlayData key
		{currency = "token", name = "Hallween Event Tokens", template = "object/tangible/loot/misc/halloween_token.iff", ScreenPlayDataString = "vendorToken", ScreenPlayDataKey = "event_token"},
	},
	--Displayed Name, full template string (without shared_), cost in {}, use the same structure as currencies
	merchandise = {
{name = "Stuffed Hutt Spawn Backpack", template = "object/tangible/wearables/backpack/backpack_gmf_01.iff", cost = {65,}},
{name = "Chiss Poacher Backpack", template = "object/tangible/wearables/backpack/ep3_chiss_poacher_player_backpack.iff", cost = {65,}},
{name = "Outbreak Prisoner Suit", template = "object/tangible/wearables/bodysuit/bodysuit_outbreak_prisoner.iff", cost = {45,}},
{name = "Gold Embroidered Cape", template = "object/tangible/tcg/series7/wearable_gold_cape.iff", cost = {95,}},
{name = "Purple Embroidered Cape", template = "object/tangible/tcg/series7/wearable_purple_cape.iff", cost = {95,}},
{name = "Skeleton Scarecrow", template = "object/tangible/storyteller/prop/pr_scarecrow_01.iff", cost = {15,}},
{name = "Stuffed Scarecrow", template = "object/tangible/storyteller/prop/pr_scarecrow_02.iff", cost = {15,}},
{name = "Ominous Painting", template = "object/tangible/event_perk/halloween_painting.iff", cost = {20,}},
{name = "Sith'o'Lantern - Cat", template = "object/tangible/event_perk/halloween_sith_o_lantern_01.iff", cost = {5,}},
{name = "Sith'o'Lantern - Face 1", template = "object/tangible/event_perk/halloween_sith_o_lantern_02.iff", cost = {5,}},
{name = "Sith'o'Lantern - Boo!", template = "object/tangible/event_perk/halloween_sith_o_lantern_03.iff", cost = {5,}},
{name = "Sith'o'Lantern - Trick or Treat", template = "object/tangible/event_perk/halloween_sith_o_lantern_04.iff", cost = {5,}},
{name = "Sith'o'Lantern - Face 2", template = "object/tangible/event_perk/halloween_sith_o_lantern_05.iff", cost = {5,}},
{name = "Skull Candle - Top", template = "object/tangible/event_perk/halloween_skull_candle_01.iff", cost = {5,}},
{name = "Skull Candle - Inside", template = "object/tangible/event_perk/halloween_skull_candle_02.iff", cost = {5,}},
{name = "Spider Web 1", template = "object/tangible/event_perk/halloween_spider_web_01.iff", cost = {5,}},
{name = "Spider Web 2", template = "object/tangible/event_perk/halloween_spider_web_02.iff", cost = {5,}},
{name = "Spider Web 3", template = "object/tangible/event_perk/halloween_spider_web_03.iff", cost = {5,}},
{name = "Outbreak Sign - Caution", template = "object/tangible/painting/painting_outbreak_biohazard_03.iff", cost = {5,}},
{name = "Outbreak Sign - Contaminated", template = "object/tangible/painting/painting_outbreak_biohazard_02.iff", cost = {5,}},
{name = "Outbreak Sign - Toxic", template = "object/tangible/painting/painting_outbreak_biohazard_01.iff", cost = {5,}},
{name = "Incarceration In the Mist", template = "object/tangible/painting/bestine_quest_painting.iff", cost = {95,}},
{name = "Schematic - Fancy Jacket (5 use)", template = "object/tangible/loot/loot_schematic/jacket_gmf_01_schematic.iff", cost = {100,}},
{name = "Schematic - BWDL19 Rifle (3 use)", template = "object/tangible/loot/loot_schematic/rifle_deathtroopers_schematic.iff", cost = {100,}},
	},
}

registerScreenPlay("HalloweenEventVendorLogic", false)