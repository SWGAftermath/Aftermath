nilyahin_apprentice = Creature:new {
	customName = "Ni'lyahin Apprentice",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "nilyahin_smugglers",
	faction = "",
	level = 86,
	chanceHit = 0.75,
	damageMin = 520,
	damageMax = 750,
	baseXp = 7207,
	baseHAM = 15000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {40,95,80,80,75,75,80,80,185},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.15,

	templates = {"object/mobile/dressed_mauler.iff"},
	lootGroups = {
		{
			groups = {
				{group = "geonosian_cubes", chance = 4000000},
				{group = "blacksun_rare", chance = 500000},
				{group = "tfa_paintings", chance = 100000},
				{group = "weapon_components", chance = 1700000},
				{group = "skill_buffs", chance = 3700000}
			},
			lootChance = 6000000
		},
	},
	weapons = {"nilyahin_apprentice"},
	conversationTemplate = "",
	attacks = merge(apprentice)
}

CreatureTemplates:addCreatureTemplate(nilyahin_apprentice, "nilyahin_apprentice")
