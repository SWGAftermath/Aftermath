nilyahin_guild_leader = Creature:new {
	customName = "Ni'lyahin Guild Leader",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "nilyahin_smugglers",
	faction = "",
	level = 157,
	chanceHit = 12.25,
	damageMin = 1020,
	damageMax = 1750,
	baseXp = 16794,
	baseHAM = 120000,
	baseHAMmax = 120000,
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

	templates = {"object/mobile/dressed_grassland_blood_marauder.iff"},
	lootGroups = {
		{
			groups = {
				{group = "blacksun_rare", chance = 500000},
				{group = "tfa_paintings", chance = 500000},
				{group = "weapon_components", chance = 3500000},
				{group = "dath_schems", chance = 2000000},
				{group = "skill_buffs", chance = 3500000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"nilyahin_old_guard"},
	conversationTemplate = "",
	attacks = merge(oldguard)
}

CreatureTemplates:addCreatureTemplate(nilyahin_guild_leader, "nilyahin_guild_leader")
