class BasicMapController{
	static string ServerMarkersPath = "\\ServerMarkers.json";
	static string BasicMapPath = "$profile:BasicMap";
	ref array<ref BasicMapMarker> ServerMarkers = new ref array<ref BasicMapMarker>;
	
	ref array<ref BasicMapMarker> ClientMarkers = new ref array<ref BasicMapMarker>;
	
	ref map< string, ref array<ref BasicMapMarker> > ModMarkers = new ref map< string, ref array<ref BasicMapMarker> >;
	
	void Init(){
		GetRPCManager().AddRPC( "BasicMap", "RPCSyncServerData", this, SingeplayerExecutionType.Both );
		if (GetGame().IsMultiplayer() && GetGame().IsClient()){
			GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param2< array<ref BasicMapMarker>, ref BasicMapConfig >( NULL, NULL ), true, NULL);
			
			LoadClientMarkers();
		} else {
			if (!FileExist(BasicMapPath + ServerMarkersPath)){
				MakeDirectory(BasicMapPath);
				ServerFirstRun();
			} else {
				 LoadServerMarkers();
			}
		}
	}
	
	void RPCSyncServerData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ){
		Param2< array<ref BasicMapMarker>, ref BasicMapConfig> data;
		if ( !ctx.Read( data ) ) return;
        if ( GetGame().IsMultiplayer() && GetGame().IsClient() ){
			ServerMarkers = data.param1;
			m_BasicMapConfig = data.param2;
			Print("[BASICMAP]Loading " + ServerMarkers.Count() + " Server Markers" );
		} else if (GetGame().IsMultiplayer() && GetGame().IsServer()){
			Print("[BASICMAP]Sending " + ServerMarkers.Count() + " Server Markers" );
			GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param2< array<ref BasicMapMarker>, ref BasicMapConfig>( ServerMarkers, GetBasicMapConfig() ), true, sender);
		}
	} 
	
	void LoadServerMarkers(){
		JsonFileLoader< array<ref BasicMapMarker> >.JsonLoadFile(BasicMapPath + ServerMarkersPath, ServerMarkers);
	}
	
	void ServerFirstRun(){
		ServerMarkers.Insert(new ref BasicMapMarker("GREEN MOUNTAIN", "BasicMap\\gui\\images\\marker.paa", Vector(3693.56, 402.312,6010.05), {212, 138, 251}));
		ServerMarkers.Insert(new ref BasicMapMarker("KUMYRNA", "BasicMap\\gui\\images\\marker.paa", Vector(8345.61, 292.302, 5985.93), {212, 138, 251}));
		JsonFileLoader< array<ref BasicMapMarker> >.JsonSaveFile(BasicMapPath + ServerMarkersPath, ServerMarkers);
	}

	
	void LoadClientMarkers(){
		string server;
        GetCLIParam("connect", server);
		string clientPath = BasicMapPath + "\\" + server + ".json";
		if (FileExist(clientPath)){
			JsonFileLoader< array<ref BasicMapMarker> >.JsonLoadFile(clientPath, ClientMarkers);
		} else {
			MakeDirectory(BasicMapPath);
			SaveClientMarkers();
		}
	}
	
	void SaveClientMarkers(){
		string server;
        GetCLIParam("connect", server);
		string clientPath = BasicMapPath + "\\" + server + ".json";
		JsonFileLoader< array<ref BasicMapMarker> >.JsonSaveFile(clientPath, ClientMarkers);
	}
	
	
	ref BasicMapMarker Marker(int i){
		int ServerMarkersIndex = 0;
		int ServerMarkersCount = ServerMarkers.Count();
		int ClientMarkersIndex = ServerMarkers.Count();
		int ClientMarkersCount = ClientMarkersIndex + ClientMarkers.Count();
		int ModMarkersIndex = ClientMarkersCount;
		int ModMarkersCount = ClientMarkersCount + ModMarkers.Count();
		if (i < ServerMarkers.Count()){
			return ServerMarkers.Get(i);
		} else if ( i < ClientMarkersCount){
			i = i - ClientMarkersIndex;
			return ClientMarkers.Get(i);
		} else if ( i < ModMarkersCount){
			i = i - ModMarkersIndex; 
			for (int j = 0; j < ModMarkers.Count(); j++){
				int nextIndex = ModMarkers.GetElement(j).Count();
				if (i < nextIndex){
					return ModMarkers.GetElement(i).Get(i);
				}
				i = i - nextIndex;
			}
		}
		return NULL;
	}
	
	int Count(){
		int count = ServerMarkers.Count() + ClientMarkers.Count();
		for (int i = 0; i < ModMarkers.Count(); i++){
			count = count + ModMarkers.GetElement(i).Count();
		}
		
		return count;
	}
	
	ref array<ref BasicMapMarker> ModMarkers(string key){
		return ModMarkers.Get(key);
	}
	
	void AddMarker(string key, ref BasicMapMarker marker){
		if (ModMarkers.Get(key)){
			ModMarkers.Get(key).Insert(marker);
		} else {
			ref array<ref BasicMapMarker> markers = new ref array<ref BasicMapMarker>;
			markers.Insert(marker);
			ModMarkers.Insert(key, markers);
		}
	}
	
	void AddMarkers(string key, ref array<ref BasicMapMarker> markers){
		if (ModMarkers.Get(key)){
			ModMarkers.Set(key, markers);
		} else {
			ModMarkers.Insert(key, markers);
		}
	}
	
	void RemoveMarkers(string key){
		if (ModMarkers.Get(key)){
			ModMarkers.Remove(key);
		}
	}
	
	void RemoveMarker(string key, ref BasicMapMarker marker){
		if (ModMarkers.Get(key)){ 
			ModMarkers.Get(key).RemoveItem(marker);
		}
	}
	
	void ClearMarkers(string key){
		if (ModMarkers.Get(key)){ 
			ModMarkers.Remove(key);
		}
	}
	
	void RemoveMarkerByIndex(string key, int index){
		if (ModMarkers.Get(key)){
			ModMarkers.Get(key).Remove(index);
		}
	}
	
	int AddClientMarker(ref BasicMapMarker marker){
		return ClientMarkers.Insert(marker);
	}
	
	ref BasicMapMarker ClientMarker(int i){
		return ClientMarkers.Get(i);
	}
	
	ref BasicMapMarker GetClientMarkerByVector(vector pos, float distance = 10){
		for (int i = 0; i < ClientMarkers.Count(); i++){
			if (vector.Distance(ClientMarkers.Get(i).GetPosition(), pos) < distance){
				return ClientMarkers.Get(i);
			}
		}
		return NULL;
	}
	
	bool RemoveClientMarkerByVector(vector pos, float distance = 10){
		for (int i = 0; i < ClientMarkers.Count(); i++){
			if (vector.Distance(ClientMarkers.Get(i).GetPosition(), pos) < distance){
				ClientMarkers.Remove(i);
				return true;
			}
		}
		return false;
	}
	
}


ref BasicMapController m_BasicMapController;

ref BasicMapController BasicMap(){
	if (!m_BasicMapController){
		m_BasicMapController = new ref BasicMapController;
		m_BasicMapController.Init();
	}
	return m_BasicMapController;
}