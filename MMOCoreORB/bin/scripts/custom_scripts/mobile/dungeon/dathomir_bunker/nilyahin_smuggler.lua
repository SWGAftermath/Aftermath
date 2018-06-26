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
	resists = {80,95,40,80,75,75,80,80,185},
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
				{group = "dath_schems", chance = 3000000},
				{group = "blacksun_rare", chance = 500000},
				{group = "tfa_paintings", chance = 100000},
				{group = "weapon_components", chance = 2000000},
				{group = "skill_buffs", chance = 3500000},
				{group = "junk", chance = 900000}
			},
			lootChance = 6000000
		}
	},
	weapons = {"nilyahin_smuggler"},
	conversationTemplate = "",
	attacks = merge(rangednil)
}

CreatureTemplates:addCreatureTemplate(nilyahin_smuggler, "nilyahin_smuggler")
