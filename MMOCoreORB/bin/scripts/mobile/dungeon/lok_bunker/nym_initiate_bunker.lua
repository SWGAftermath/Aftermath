nym_initiate_bunker = Creature:new {
	customName = "Force-wielding Nym's Initiate",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "nym",
	level = 60,
	chanceHit = 0.5,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5830,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {10,10,10,100,100,100,100,100,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_nym_guard_weak_hum_f.iff",
		"object/mobile/dressed_nym_guard_weak_rod_m.iff",
		"object/mobile/dressed_nym_guard_weak_nikto_m.iff",
		"object/mobile/dressed_nym_guard_weak_hum_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "nyms_common", chance = 1000000},
				{group = "armor_attachments", chance = 250000},
				{group = "clothing_attachments", chance = 250000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "tailor_components", chance = 500000}
			}
		}
	},
	weapons = {"mixed_force_weapons"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(tkamid,fencermid,swordsmanmid,pikemanmid,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(nym_initiate_bunker, "nym_initiate_bunker")
