nilyahin_smuggler = Creature:new {
	customName = "Ni'lyahin Smuggler",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "nilyahin_smugglers",
	faction = "",
	level = 96,
	chanceHit = 0.95,
	damageMin = 620,
	damageMax = 950,
	baseXp = 9057,
	baseHAM = 22000,
	baseHAMmax = 22000,
	armor = 2,
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

	templates = {"object/mobile/dressed_nym_guard_weak_hum_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "death_watch_bunker_commoners", chance = 9900000},
				{group = "blacksun_rare", chance = 100000}
			},
			lootChance = 1000000
		}
	},
	weapons = {"nilyahin_smuggler"},
	conversationTemplate = "",
	attacks = merge(oldguard)
}

CreatureTemplates:addCreatureTemplate(nilyahin_smuggler, "nilyahin_smuggler")
