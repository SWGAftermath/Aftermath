nuna_alpha = Creature:new {
	customName = "Genetically Modified Nuna",
	socialGroup = "self",
	faction = "",
	level = 200,
	chanceHit = 30.0,
	damageMin = 1900,
	damageMax = 3100,
	baseXp = 19200,
	baseHAM = 96000,
	baseHAMmax = 118000,
	armor = 2,
	resists = {45,45,45,45,45,45,45,45,45},
	meatType = "meat_avian",
	meatAmount = 3,
	hideType = "hide_leathery",
	hideAmount = 4,
	boneType = "bone_avian",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	scale = 4,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/nuna.iff"},
	controlDeviceTemplate = "object/intangible/pet/nuna_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nuna_alpha, "nuna_alpha")
