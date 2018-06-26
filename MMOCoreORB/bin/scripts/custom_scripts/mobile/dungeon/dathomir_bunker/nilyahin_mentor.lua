nilyahin_mentor = Creature:new {
	customName = "Ni'lyahin Mentor",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "nilyahin_smugglers",
	faction = "",
	level = 121,
	chanceHit = 4,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 11390,
	baseHAM = 50000,
	baseHAMmax = 50000,
	armor = 2,
	resists = {80,95,80,80,75,75,40,80,185},
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

	templates = {"object/mobile/dressed_hutt_informant_quest.iff"},
	lootGroups = {
		{
			groups = {
				{group = "blacksun_rare", chance = 500000},
				{group = "tfa_paintings", chance = 100000},
				{group = "weapon_components", chance = 3500000},
				{group = "dath_schems", chance = 2200000},
				{group = "skill_buffs", chance = 3700000}
			},
			lootChance = 6000000
		}
	},
	weapons = {"nilyahin_mentor"},
	conversationTemplate = "",
	attacks = merge(mentor)
}

CreatureTemplates:addCreatureTemplate(nilyahin_mentor, "nilyahin_mentor")
