nilyahin_assassin = Creature:new {
	customName = "Ni'lyahin Assassin",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "nilyahin_smugglers",
	faction = "",
	level = 107,
	chanceHit = 1.75,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 10081,
	baseHAM = 40000,
	baseHAMmax = 40000,
	armor = 2,
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

	templates = {"object/mobile/dressed_nym_guard_strong_nikto_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "geonosian_cubes", chance = 4000000},
				{group = "blacksun_rare", chance = 500000},
				{group = "tfa_paintings", chance = 500000},
				{group = "weapon_components", chance = 1500000},
				{group = "skill_buffs", chance = 3500000}
			},
			lootChance = 6000000
		}
	},
	weapons = {"nilyahin_assassin"},
	conversationTemplate = "",
	attacks = merge(unarmednil)
}

CreatureTemplates:addCreatureTemplate(nilyahin_assassin, "nilyahin_assassin")
