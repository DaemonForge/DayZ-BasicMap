class BasicMapController{
	static string ServerMarkersPath = "\\ServerMarkers.json";
	static string BasicMapPath = "$profile:BasicMap";
	
	static string SERVER_KEY = "BASICMAP_SERVER";
	static string CLIENT_KEY = "BASICMAP_CLIENT";
	
	static string InfoText = "<p>Double Left-Click to Create Marker</p><p>Double Right-Click to Delete Marker</p>";
		
	ref map< string, ref array<ref BasicMapMarker> > Markers = new ref map< string, ref array<ref BasicMapMarker> >;
	
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
			Markers.Set(SERVER_KEY,data.param1);
			m_BasicMapConfig = data.param2;
		} else if (GetGame().IsMultiplayer() && GetGame().IsServer()){
			array<ref BasicMapMarker> ServerMarkers = new array<ref BasicMapMarker>;
			if (Markers.Get(SERVER_KEY)){
				ServerMarkers = Markers.Get(SERVER_KEY);
			}
			Print("[BASICMAP]Sending " + ServerMarkers.Count() + " Server Markers" );
			GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param2< array<ref BasicMapMarker>, ref BasicMapConfig>( ServerMarkers, GetBasicMapConfig() ), true, sender);
		}
	} 
	
	void LoadServerMarkers(){
		array<ref BasicMapMarker> ServerMarkers;
		JsonFileLoader< array<ref BasicMapMarker> >.JsonLoadFile(BasicMapPath + ServerMarkersPath, ServerMarkers);
		if (ServerMarkers){
			Markers.Set(SERVER_KEY, ServerMarkers);
		}
	}
	
	void ServerFirstRun(){
		array<ref BasicMapMarker> ServerMarkers;
		ServerMarkers.Insert(new ref BasicMapMarker("GREEN MOUNTAIN", Vector(3693.56, 402.312,6010.05), "BasicMap\\gui\\images\\marker.paa", {212, 138, 251}));
		ServerMarkers.Insert(new ref BasicMapMarker("KUMYRNA", Vector(8345.61, 292.302, 5985.93), "BasicMap\\gui\\images\\marker.paa", {212, 138, 251}));
		for (int i = 0; i < ServerMarkers.Count(); i++){
			ServerMarkers.Get(i).SetCanEdit(false);
			ServerMarkers.Get(i).SetGroup(SERVER_KEY);
		}
		Markers.Set(SERVER_KEY, ServerMarkers);
		JsonFileLoader< array<ref BasicMapMarker> >.JsonSaveFile(BasicMapPath + ServerMarkersPath, ServerMarkers);
	}

	
	void LoadClientMarkers(){
		string server;
        GetCLIParam("connect", server);
		string clientPath = BasicMapPath + "\\" + server + ".json";
		if (FileExist(clientPath)){
			ref array<ref BasicMapMarker> ClientMarkers = new ref array<ref BasicMapMarker>;
			JsonFileLoader< array<ref BasicMapMarker> >.JsonLoadFile(clientPath, ClientMarkers);
			for (int i = 0; i < ClientMarkers.Count(); i++){
				ClientMarkers.Get(i).SetCanEdit(true);
				ClientMarkers.Get(i).SetGroup(CLIENT_KEY);
			}
			Markers.Set(CLIENT_KEY, ClientMarkers);
		} else {
			MakeDirectory(BasicMapPath);
			SaveClientMarkers();
		}
	}
	
	void SaveClientMarkers(){
		ref array<ref BasicMapMarker> ClientMarkers = new ref array<ref BasicMapMarker>;
		string server;
        GetCLIParam("connect", server);
		string clientPath = BasicMapPath + "\\" + server + ".json";
		if (Markers.Get(CLIENT_KEY)){
			ClientMarkers = Markers.Get(CLIENT_KEY);
		}
		JsonFileLoader< array<ref BasicMapMarker> >.JsonSaveFile(clientPath, ClientMarkers);
	}
	
	
	ref BasicMapMarker Marker(int i){
		for (int j = 0; j < Markers.Count(); j++){
			int nextIndex = Markers.GetElement(j).Count();
			if (i < nextIndex){
				return Markers.GetElement(j).Get(i);
			}
			i = i - nextIndex;
		}
		return NULL;
	}
	
	int Count(){
		int count = 0;
		for (int i = 0; i < Markers.Count(); i++){
			count = count + Markers.GetElement(i).Count();
		}
		return count;
	}
	
	ref array<ref BasicMapMarker> GetMarkers(string key){
		return Markers.Get(key);
	}
	
	void AddMarker(string key, ref BasicMapMarker marker){
		if (Markers.Get(key)){
			marker.SetGroup(key);
			Markers.Get(key).Insert(marker);
		} else {
			ref array<ref BasicMapMarker> markers = new ref array<ref BasicMapMarker>;
			marker.SetGroup(key);
			markers.Insert(marker);
			Markers.Insert(key, markers);
		}
	}
	
	void SetMarkers(string key, ref array<ref BasicMapMarker> markers){
		if (Markers.Get(key)){
			Markers.Set(key, markers);
		} else {
			Markers.Insert(key, markers);
		}
	}
	
	void RemoveAllMarkers(string key){
		if (Markers.Get(key)){
			Markers.Remove(key);
		}
	}
	
	void RemoveMarker(string key, ref BasicMapMarker marker){
		if (Markers.Get(key)){ 
			Markers.Get(key).RemoveItem(marker);
		}
	}
	
	bool RemoveMarker(ref BasicMapMarker marker){
		for (int j = 0; j < Markers.Count(); j++){
			for (int k = 0; k < Markers.GetElement(j).Count(); k++){
				if (marker == Markers.GetElement(j).Get(k)){
					Markers.GetElement(j).Remove(k);
					return true;
				}
			}
		}
		return false;
	}
	
	void ClearMarkers(string key){
		if (Markers.Get(key)){ 
			Markers.Get(key).Clear();
		}
	}
	
	void RemoveMarkerByIndex(string key, int index){
		if (Markers.Get(key)){
			Markers.Get(key).Remove(index);
		}
	}
	
	ref array<ref BasicMapMarker> ClientMarkers(){
		return Markers.Get(CLIENT_KEY);
	}
	
	int AddClientMarker(ref BasicMapMarker marker){
		if ( Markers.Get(CLIENT_KEY)){
			marker.SetCanEdit(true);
			marker.SetGroup(CLIENT_KEY);
			return Markers.Get(CLIENT_KEY).Insert(marker);
		}
		return -1;
	}
	
	ref BasicMapMarker ClientMarker(int i){
		if ( Markers.Get(CLIENT_KEY)){
			return Markers.Get(CLIENT_KEY).Get(i);
		}
		return NULL;
	}
	
	ref BasicMapMarker GetMarkerByVector(vector pos, float distance = 10){
		for (int j = 0; j < Markers.Count(); j++){
			for (int k = 0; k < Markers.GetElement(j).Count(); k++){
				if (vector.Distance(Markers.GetElement(j).Get(k).GetPosition(), pos) < distance && Markers.GetElement(j).Get(k).Editable()){
					Markers.GetElement(j).Get(k).SetGroup(Markers.GetKey(j));
					return Markers.GetElement(j).Get(k);
				}
			}
		}
		return NULL;
	}
	
	bool RemoveMarkerByVector(vector pos, float distance = 10){
		for (int j = 0; j < Markers.Count(); j++){
			for (int k = 0; k < Markers.GetElement(j).Count(); k++){
				if (vector.Distance(Markers.GetElement(j).Get(k).GetPosition(), pos) < distance && Markers.GetElement(j).Get(k).Editable()){
					Markers.GetElement(j).Remove(k);
					return true;
				}
			}
		}
		return false;
	}
	
	static string GetInfoText(){
		return InfoText;
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