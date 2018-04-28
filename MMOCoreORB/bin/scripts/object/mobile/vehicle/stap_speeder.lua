-- Aftermath

object_mobile_vehicle_stap_speeder = object_mobile_vehicle_shared_stap_speeder:new {
	templateType = VEHICLE,
	decayRate = 15, -- Damage tick per decay cycle
	decayCycle = 600 -- Time in seconds per cycle
}
ObjectTemplates:addTemplate(object_mobile_vehicle_stap_speeder, "object/mobile/vehicle/stap_speeder.iff")
