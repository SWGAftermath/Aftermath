cu_pa_alpha = Creature:new {
	customName = "Genetically Enhanced Cu-Pa",
	socialGroup = "cu_pa",
	faction = "",
	level = 211,
	chanceHit = 30.0,
	damageMin = 1900,
	damageMax = 3300,
	baseXp = 3560,
	baseHAM = 100000,
	baseHAMmax = 120000,
	armor = 2,
	resists = {50,50,50,50,50,50,50,50,50},
	meatType = "meat_reptilian",
	meatAmount = 215,
	hideType = "hide_bristley",
	hideAmount = 100,
	boneType = "bone_mammal",
	boneAmount = 115,
	milkType = "milk_wild",
	milk = 100,
	tamingChance = 0.25,
	ferocity = 0,
	scale = 3,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/cu_pa_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/cu_pa_hue.iff",
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(cu_pa_alpha, "cu_pa_alpha")
