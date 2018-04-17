housemerch = Creature:new {
	objectName = "@mob/creature_names:commoner",
	customName = "A Shady Looking Dealer",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 1,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 1,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = 264, --for conversation
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_assassin_mission_giver_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "housemerch_template",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(housemerch, "housemerch")
