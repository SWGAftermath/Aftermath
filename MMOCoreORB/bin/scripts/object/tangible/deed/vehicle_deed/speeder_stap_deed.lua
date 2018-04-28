-- Aftermath

object_tangible_deed_vehicle_deed_speeder_stap_deed = object_tangible_deed_vehicle_deed_shared_speeder_stap_deed:new {

	templateType = VEHICLEDEED,

	controlDeviceObjectTemplate = "object/intangible/vehicle/stap_speeder_pcd.iff",
	generatedObjectTemplate = "object/mobile/vehicle/stap_speeder.iff",

	numberExperimentalProperties = {1, 1, 1},
	experimentalProperties = {"XX", "XX", "SR"},
	experimentalWeights = {1, 1, 1},
	experimentalGroupTitles = {"null", "null", "exp_durability"},
	experimentalSubGroupTitles = {"null", "null", "hit_points"},
	experimentalMin = {0, 0, 1500},
	experimentalMax = {0, 0, 3000},
	experimentalPrecision = {0, 0, 0},
	experimentalCombineType = {0, 0, 1},
}
ObjectTemplates:addTemplate(object_tangible_deed_vehicle_deed_speeder_stap_deed, "object/tangible/deed/vehicle_deed/speeder_stap_deed.iff")
