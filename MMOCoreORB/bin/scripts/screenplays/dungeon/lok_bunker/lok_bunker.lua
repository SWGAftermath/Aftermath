LokBunkerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "LokBunkerScreenPlay",

registerScreenPlay("LokBunkerScreenPlay", true)

}

function LokBunkerScreenPlay:start()
	if (isZoneEnabled("lok")) then
                self:spawnMobiles()
				self:spawnSceneObjects()
                --self:initializeLootContainers()
        end
end

function LokBunkerScreenPlay:spawnSceneObjects()

	
end

function LokBunkerScreenPlay:spawnMobiles()
--Outside
	spawnMobile("lok", "nym_initiate_bunker", 600, 3740.4, 12.0, -3079.2, -70, 0)
	spawnMobile("lok", "nym_initiate_bunker", 600, 3742.6, 12.1, -3072.9, -70, 0)
--Inside
	spawnMobile("lok", "nym_ranger_bunker", 720,  -10.6, -17.0, 75.8, 179, 9686007)
	spawnMobile("lok", "nym_sentinel_bunker", 720, 7.7, -9.0, 28.9, 176, 9686003)
	spawnMobile("lok", "nym_ranger_bunker", 720, -1.0, -9.0, 29.0, 176, 9686003)
	spawnMobile("lok", "nym_spellweaver_bunker", 720, -10.5, -9.0, 34.7, 179, 9686007)
	spawnMobile("lok", "nym_protector_bunker", 1200, -5.5, -17.0, 63.1, -89, 9686007)
	spawnMobile("lok", "nym_initiate_bunker", 600, -38.5, -19.0, 82.6, 178, 9686008)
	spawnMobile("lok", "nym_protector_bunker", 1200, -42.9, -23.0, 103.1, 85, 9686008)
	spawnMobile("lok", "nym_spellweaver_bunker", 720, 15.0, -23.0, 103.7, -91, 9686008)
	spawnMobile("lok", "nym_ranger_bunker", 720, 9.5, -19.0, 81.6, 177, 9686008)
	spawnMobile("lok", "nym_protector_bunker", 1200, 37.2, -21.0, 133.3, 178, 9686009)
	spawnMobile("lok", "nym_protector_bunker", 1200, 37.5, -21.0, 153.1, 179, 9686009)
	spawnMobile("lok", "nym_elder_bunker", 3600, 2.4, -23.0, 284.0, -179, 9686015)
	spawnMobile("lok", "nym_protector_bunker", 1200, -38.1, -23.0, 199.0, 179, 9686008)
	spawnMobile("lok", "nym_protector_bunker", 1200, 9.5, -23.0, 199.8, 175, 9686008)
	spawnMobile("lok", "nym_elder_bunker", 3600, -87.8, -23.0, 232.9, 174, 9686012)
	spawnMobile("lok", "nym_slave_bunker", 300, -9.0, -23.0, 143.5, -176, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -3.7, -23.0, 136.2, -178, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -11.7, -23.0, 131.0, 87, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -25.0, -23.0, 144.9, -174, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -18.2, -23.0, 136.4, 178, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -18.7, -23.0, 151.1, 93, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -18.7, -23.0, 163.0, -1, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -26.7, -23.0, 171.4, -92, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -5.4, -23.0, 165.8, 179, 9686008)
	spawnMobile("lok", "nym_slave_bunker", 300, -10.2, -23.0, 176.7, 2, 9686008)
	spawnMobile("lok", "nym_initiate_bunker", 600, 9.2, -23.0, 220.3, -175, 9686013)
	spawnMobile("lok", "nym_ranger_bunker", 720, -2.4, -23.0, 247.4, -177, 9686016)
	spawnMobile("lok", "nym_sentinel_bunker", 720, 10.8, -23.0, 275.9, -177, 9686015)
	spawnMobile("lok", "nym_spellweaver_bunker", 720, -4.1, -23.0, 269.1, 86, 9686015)
	spawnMobile("lok", "nym_spellweaver_bunker", 720, 29.4, -23.0, 253.0, 177, 9686016)
	spawnMobile("lok", "nym_protector_bunker", 1200, 23.6, -23.0, 219.4, -90, 9686011)
	spawnMobile("lok", "nym_slave_bunker", 300, 37.8, -23.0, 206.4, -1, 9686011)
	spawnMobile("lok", "nym_slave_bunker", 300, 44.8, -23.0, 206.2, 0, 9686011)
	spawnMobile("lok", "nym_slave_bunker", 300, 51.5, -23.0, 233.6, 178, 9686011)
	spawnMobile("lok", "nym_ranger_bunker", 720, -53.1, -23.0, 219.3, 89, 9686012)
	spawnMobile("lok", "nym_slave_bunker", 300, -73.6, -23.0, 205.1, -1, 9686012)
	spawnMobile("lok", "nym_slave_bunker", 300, -80.5, -23.0, 232.8, -178, 9686012)
	spawnMobile("lok", "nym_sentinel_bunker", 720, -89.2, -21.0, 223.3, -177, 9686012)
	spawnMobile("lok", "nym_spellweaver_bunker", 720, -85.8, -21.0, 223.5, -177, 9686012)
	spawnMobile("lok", "nym_elder_bunker", 3600, 70.7, -23.0, 219.1, -90, 9686011)
end