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
	resists = {55,55,70,60,30,30,100,40,-1},
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
				{group = "death_watch_bunker_commoners", chance = 6000000},
				{group = "death_watch_bunker_lieutenants", chance = 4000000}
			},
			lootChance = 1000000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(bountyhuntermaster,marksmanmaster,brawlermaster,tkamaster)
}

CreatureTemplates:addCreatureTemplate(nilyahin_mentor, "nilyahin_mentor")
