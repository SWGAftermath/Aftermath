nilyahin_apprentice = Creature:new {
	customName = "Ni'lyahin Apprentice",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "nilyahin_smugglers",
	faction = "",
	level = 86,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 7207,
	baseHAM = 13000,
	baseHAMmax = 16000,
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
				{group = "geonosian_cubes", chance = 4400000},
				{group = "blacksun_rare", chance = 100000},
				{group = "tfa_paintings", chance = 100000},
				{group = "weapon_components", chance = 1700000},
				{group = "skill_buffs", chance = 3700000}
			},
			lootChance = 6000000
		},
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(bountyhuntermaster,marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(nilyahin_apprentice, "nilyahin_apprentice")
