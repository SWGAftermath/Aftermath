nilyahin_specialist = Creature:new {
	customName = "Ni'lyahin  Specialist",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "nilyahin_smugglers",
	faction = "",
	level = 86,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8130,
	baseHAM = 15000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {40,40,60,35,55,70,35,40,-1},
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

	templates = {"object/mobile/dressed_rebel_first_lieutenant_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "death_watch_bunker_commoners", chance = 9900000},
				{group = "blacksun_rare", chance = 100000}
			},
			lootChance = 1000000
		}
	},
	weapons = {"nilyahin_specialist"},
	conversationTemplate = "",
	attacks = merge(specialist)
}

CreatureTemplates:addCreatureTemplate(nilyahin_specialist, "nilyahin_specialist")
