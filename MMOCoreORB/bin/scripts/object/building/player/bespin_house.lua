object_building_player_bespin_house = object_building_player_shared_bespin_house:new {
	lotSize = 5,
	baseMaintenanceRate = 50,
	allowedZones = {"dantooine", "lok", "tatooine", "naboo", "rori", "corellia", "talus"},
	publicStructure = 0,
	constructionMarker = "object/building/player/construction/construction_player_house_corellia_large_style_01.iff",
	length = 1,
	width = 1,
	skillMods = {
		{"private_medical_rating", 100},
		{"private_buff_mind", 100},
		{"private_med_battle_fatigue", 5},
		{"private_safe_logout", 1}	
	},
	childObjects = {
			{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = -1.75983, z = 88.8802, y = 4.3361, ow = 0.173648, ox = 0, oz = 0, oy = 0.984808, cellid = 2, containmentType = -1},
			{templateFile = "object/tangible/terminal/terminal_elevator_up.iff", x = 0.680352, z = 0.631912, y = 1.11112, ow = -0.258819, ox = 0, oy = 0.965926, oz = 0, cellid = 1, containmentType = -1},
			{templateFile = "object/tangible/terminal/terminal_elevator_down.iff", x = 0.680352, z = 88.8368, y = 1.11112, ow = -0.258819, ox = 0, oy = 0.965926, oz = 0, cellid = 1, containmentType = -1},
			{templateFile = "object/tangible/sign/player/house_address.iff", x = 0.39, z = 3.00, y = -2.44, ow = 0.99144, ox = 0, oz = 0, oy = -0.13053, cellid = -1, containmentType = -1}
	},
	shopSigns = {
			{templateFile = "object/tangible/sign/player/house_address.iff", x = 0.39, z = 3.00, y = -2.44, ow = 0.99144, ox = 0, oz = 0, oy = -0.13053, cellid = -1, containmentType = -1, requiredSkill = "", suiItem = "@player_structure:house_address"},
			{templateFile = "object/tangible/sign/player/shop_sign_s01.iff", x = -0.532527, z = 0.531912, y = -5.45694, ow = 1, ox = 0, oz = 0, oy = 0, cellid = -1, containmentType = -1, requiredSkill = "crafting_merchant_management_01", suiItem = "@player_structure:shop_sign1"},
			{templateFile = "object/tangible/sign/player/shop_sign_s02.iff", x = -0.532527, z = 0.531912, y = -5.45694, ow = 1, ox = 0, oz = 0, oy = 0, cellid = -1, containmentType = -1, requiredSkill = "crafting_merchant_management_02", suiItem = "@player_structure:shop_sign2"},
			{templateFile = "object/tangible/sign/player/shop_sign_s03.iff", x = -0.532527, z = 0.531912, y = -5.45694, ow = 1, ox = 0, oz = 0, oy = 0, cellid = -1, containmentType = -1, requiredSkill = "crafting_merchant_management_03", suiItem = "@player_structure:shop_sign3"},
			{templateFile = "object/tangible/sign/player/shop_sign_s04.iff", x = -0.532527, z = 0.531912, y = -5.45694, ow = 1, ox = 0, oz = 0, oy = 0, cellid = -1, containmentType = -1, requiredSkill = "crafting_merchant_management_04", suiItem = "@player_structure:shop_sign4"}
	}
}

ObjectTemplates:addTemplate(object_building_player_bespin_house, "object/building/player/bespin_house.iff")