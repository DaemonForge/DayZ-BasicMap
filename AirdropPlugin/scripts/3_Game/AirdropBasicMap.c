class AirdropBasicMapConfig
{
	protected static string ConfigPATH = "$profile:BasicMap\\AirDrop.json";
	string ConfigVersion = "1";
	float CircleRndRadius = 150;
	float CircleDrawRadius = 200;
	vector CircleColor = "237 59 110";
	
	void Load(){
		if (GetGame().IsServer()){
			if (FileExist(ConfigPATH)){ //If config exist load File
			    JsonFileLoader<AirdropBasicMapConfig>.JsonLoadFile(ConfigPATH, this);
				if (ConfigVersion != "1"){
					ConfigVersion = "1";
					CircleRndRadius = 150;
					CircleDrawRadius = 150;
					CircleColor = "237 59 110";
					Save();
				}
			}else{ //File does not exist create file	
				Save();
			}
		}
	}
	
	void Save(){
			JsonFileLoader<AirdropBasicMapConfig>.JsonSaveFile(ConfigPATH, this);
	}
	
}
ref AirdropBasicMapConfig m_AirdropBasicMapConfig;

//Helper function to return Config
static ref AirdropBasicMapConfig GetAirdropBasicMapConfig()
{
	if (!m_AirdropBasicMapConfig)
	{
		m_AirdropBasicMapConfig = new ref AirdropBasicMapConfig;
			
		if ( GetGame().IsServer() ){
			m_AirdropBasicMapConfig.Load();
		}
	}
	return m_AirdropBasicMapConfig;
};