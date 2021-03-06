kylaena_haley = Creature:new {
	objectName = "@mob/creature_names:kylaena_haley",
	socialGroup = "sith_shadow",
	faction = "sith_shadow",
	level = 103,
	chanceHit = 0.9,
	damageMin = 720,
	damageMax = 1150,
	baseXp = 9801,
	baseHAM = 15900,
	baseHAMmax = 19400,
	armor = 0,
	resists = {80,80,80,80,80,80,80,80,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + HEALER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_fs_village_enemy_kylaena.iff"},
	lootGroups = {},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,pikemanmaster)
}

CreatureTemplates:addCreatureTemplate(kylaena_haley, "kylaena_haley")
