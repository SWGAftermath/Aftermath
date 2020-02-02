ForceCrystalCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "ForceCrystalCaveScreenPlay",

	lootContainers = {
		200335,
		200336,		
		8535511			
	},
	
	lootLevel = 36,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 3500000},
				{group = "junk", chance = 3500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("ForceCrystalCaveScreenPlay", true)

function ForceCrystalCaveScreenPlay:start()
	if (isZoneEnabled("dantooine")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function ForceCrystalCaveScreenPlay:spawnMobiles()   
	spawnMobile("dantooine", "force_crystal_hunter",900,89,-62,-13.4,-139,8535485)
	spawnMobile("dantooine", "force_crystal_hunter",900,52.5,-67.9,-42.9,32,8535484)
	spawnMobile("dantooine", "force_crystal_hunter",900,76.3,-77,-89.3,-81,8535486)
	spawnMobile("dantooine", "force_crystal_hunter",900,95.5555,-68.0662,-39.6769,318,8535485)
	
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,64.1,-68.9,-36.8,86,8535485)
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,85.3,-77.2,-62.9,-57,8535486)
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,54.3963,-68.2445,-41.9985,253,8535484)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,52.2831,-67.9229,-40.4875,160,8535484) 
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,85.102,-76.1262,-59.5219,171,8535486) 
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,67.5089,-75.2068,-62.4254,315,8535486)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,67.4846,-75.4452,-59.3925,212,8535486)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,55.0766,-48.9898,-55.0631,219,8535484)  	
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,53.3728,-48.2447,-66.0768,264,8535484)  	
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,24.0356,-42.2643,-69.56,254,8535484)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,66.6039,-57.2558,-20.6332,328,8535485)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,93.9963,-67.8841,-39.1217,87,8535485)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,24.6478,-27.0582,-6.99768,25,8535483)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,21.8116,-29.9439,-15.183,296,8535483)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,45.4485,-47.0834,-7.67292,101,8535484)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,91.3987,-61.4116,-7.87201,25,8535485)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,65.2081,-75.3395,-60.3233,95,8535486)  
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",900,-13.0484,-5.52473,-11.202,246,8535483)
	
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,0.7,-13.6,-6.9,-82,8535483)
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,65.6,-77,-78.4,-10,8535486)
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,23.8,-38.4,-32.8,-2,8535484)
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,49.8,-48.5,-65.6,92,8535484)
    spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,48.5024,-46.9394,-6.45166,232,8535484)
    spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,20.1675,-41.1525,-70.1508,49,8535484)
    spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,88.6634,-62.0338,-16.4253,334,8535485)  
    spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,66.0494,-56.8511,-19.6552,150,8535485)
    spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",900,93.1801,-76.1547,-83.775,84,8535486)
end
