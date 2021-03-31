class BasicMapConfig
{
	protected static string ConfigPATH = "$profile:BasicMap\\ServerSettings.json";
	string ConfigVersion = "1";
	ref TStringArray Icons = { 
		"BasicMap\\gui\\images\\marker.paa", 
		"BasicMap\\gui\\images\\location.paa", 
		"BasicMap\\gui\\images\\info.paa", 
		"BasicMap\\gui\\images\\guns.paa", 
		"BasicMap\\gui\\images\\pin.paa", 
		"BasicMap\\gui\\images\\shop.paa", 
		"BasicMap\\gui\\images\\atm.paa", 
		"BasicMap\\gui\\images\\cart.paa", 
		"BasicMap\\gui\\images\\tent.paa", 
		"BasicMap\\gui\\images\\house.paa", 
		"BasicMap\\gui\\images\\warn.paa", 
		"BasicMap\\gui\\images\\heli.paa", 
		"BasicMap\\gui\\images\\car.paa", 
		"BasicMap\\gui\\images\\flag.paa", 
		"BasicMap\\gui\\images\\watertower.paa", 
		"BasicMap\\gui\\images\\police.paa", 
		"BasicMap\\gui\\images\\hospital.paa", 
		"BasicMap\\gui\\images\\well.paa",
		"DZ\\gear\\navigation\\data\\map_border_cross_ca.paa",
		"DZ\\gear\\navigation\\data\\map_chapel_ca.paa",
		"DZ\\gear\\navigation\\data\\map_church_ca.paa",
		"DZ\\gear\\navigation\\data\\map_cross_ca.paa",
		"DZ\\gear\\navigation\\data\\map_factory_ca.paa",
		"DZ\\gear\\navigation\\data\\map_fir_ca.paa",
		"DZ\\gear\\navigation\\data\\map_firedep_ca.paa",
		"DZ\\gear\\navigation\\data\\map_fortress_ca.paa",
		"DZ\\gear\\navigation\\data\\map_fountain_ca.paa",
		"DZ\\gear\\navigation\\data\\map_fuelstation_ca.paa",
		"DZ\\gear\\navigation\\data\\map_govoffice_ca.paa",
		"DZ\\gear\\navigation\\data\\map_hill_ca.paa",
		"DZ\\gear\\navigation\\data\\map_hospital_ca.paa",
		"DZ\\gear\\navigation\\data\\map_lighthouse_ca.paa",
		"DZ\\gear\\navigation\\data\\map_monument_ca.paa",
		"DZ\\gear\\navigation\\data\\map_palm_ca.paa",
		"DZ\\gear\\navigation\\data\\map_police_ca.paa",
		"DZ\\gear\\navigation\\data\\map_quay_ca.paa",
		"DZ\\gear\\navigation\\data\\map_rock_ca.paa",
		"DZ\\gear\\navigation\\data\\map_ruin_ca.paa",
		"DZ\\gear\\navigation\\data\\map_shipwreck_ca.paa",
		"DZ\\gear\\navigation\\data\\map_stack_ca.paa",
		"DZ\\gear\\navigation\\data\\map_station_ca.paa",
		"DZ\\gear\\navigation\\data\\map_store_ca.paa",
		"DZ\\gear\\navigation\\data\\map_tourism_ca.paa",
		"DZ\\gear\\navigation\\data\\map_transmitter_ca.paa",
		"DZ\\gear\\navigation\\data\\map_tshelter_ca.paa",
		"DZ\\gear\\navigation\\data\\map_tsign_ca.paa",
		"DZ\\gear\\navigation\\data\\map_viewpoint_ca.paa",
		"DZ\\gear\\navigation\\data\\map_viewtower_ca.paa",
		"DZ\\gear\\navigation\\data\\map_vineyard_ca.paa",
		"DZ\\gear\\navigation\\data\\map_waterpump_ca.paa",
		"DZ\\gear\\navigation\\data\\map_watertower_ca.paa"
	};
	bool AllowPlayerMarkers = true;
	bool Allow3dMarkers = true;
	bool ShowSelfOnMap = true;
	bool RequireMapItemInInventory = false;
	bool OnlyOnOpenAction = false;
	bool RequirePenToMark = false;
	bool SaveMarkersToMapItem = false; // Requires `OnlyOnOpenAction` or `RequireMapItemInInventory`
	bool RequireCompassToSeeSelf = false;
	bool RequireCompassToSee3d = false;
	
	void Load(){
		if (GetGame().IsServer()){
			if (FileExist(ConfigPATH)){ //If config exist load File
			    JsonFileLoader<BasicMapConfig>.JsonLoadFile(ConfigPATH, this);
				if (ConfigVersion != "1"){
					ConfigVersion = "1";
					ShowSelfOnMap = true;
					RequireMapItemInInventory = false; 
					OnlyOnOpenAction = false;
					RequirePenToMark = false;
					SaveMarkersToMapItem = false;
					RequireCompassToSeeSelf = false;
					RequireCompassToSee3d = false;
					Save();
				}
			}else{ //File does not exist create file	
				Save();
			}
		}
	}
	
	void Save(){
			JsonFileLoader<BasicMapConfig>.JsonSaveFile(ConfigPATH, this);
	}
	
}
ref BasicMapConfig m_BasicMapConfig;

//Helper function to return Config
static ref BasicMapConfig GetBasicMapConfig()
{
	if (!m_BasicMapConfig)
	{
		m_BasicMapConfig = new BasicMapConfig;
			
		if ( GetGame().IsServer()){
			m_BasicMapConfig.Load();
		}
	}
	return m_BasicMapConfig;
};