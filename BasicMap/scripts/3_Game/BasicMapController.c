class BasicMapController{
	static string ServerMarkersPath = "\\ServerMarkers.json";
	static string BasicMapPath = "$profile:BasicMap";
	
	protected bool MarkersOnHUD = true;
	
	static string SERVER_KEY = "BASICMAP_SERVER";
	static string CLIENT_KEY = "BASICMAP_CLIENT";
	
	static string PARTY_KEY = "";
	
	static string InfoText = "<p>Double Left-Click to Create Marker</p><p>Double Right-Click to Delete Marker</p>";
		
	ref map< string, ref array<ref BasicMapMarker> > Markers = new ref map< string, ref array<ref BasicMapMarker> >;
	
	//GROUP NAME DISPLAYNAME? or MetaDataObject?
	ref map< string, ref BasicMapGroupMetaData> Groups = new map<string, ref BasicMapGroupMetaData>;
	ref map<string, ref BasicMapMarkerFactory> Factories = new map<string, ref BasicMapMarkerFactory>;
	
	void Init(){
		GetRPCManager().AddRPC( "BasicMap", "RPCSyncServerData", this, SingeplayerExecutionType.Both );
		RegisterGroup(SERVER_KEY, new ref BasicMapGroupMetaData(SERVER_KEY, "SERVER MARKERS"), NULL);
		RegisterGroup(CLIENT_KEY, new ref BasicMapGroupMetaData(CLIENT_KEY, "PERSONAL MARKERS", true), new ref BasicMapMarkerFactory());
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
	
	ref map< string, ref BasicMapGroupMetaData> GetGroups(){
		return Groups;
	}
	
	ref BasicMapGroupMetaData GetGroup(string id){
		return Groups.Get(id);
	}
	
	string GetGroupName(string id){
		return Groups.Get(id).GetDisplayName();
	}
	
	void RegisterGroup(string id, ref BasicMapGroupMetaData metaData, ref BasicMapMarkerFactory factory){
		Groups.Insert(id, metaData);
		Factories.Insert(id, factory);
	}
	
	
	
	void RPCSyncServerData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ){
		Param2< array<ref BasicMapMarker>, ref BasicMapConfig> data;
		array<ref BasicMapMarker> ServerMarkers = new array<ref BasicMapMarker>;
		if ( !ctx.Read( data ) ) return;
        if ( GetGame().IsMultiplayer() && GetGame().IsClient() ){
			ServerMarkers =  data.param1;
			for ( int i = 0; i < ServerMarkers.Count(); i++){
				ServerMarkers.Get(i).SetCanEdit(false);
				ServerMarkers.Get(i).SetGroup(SERVER_KEY);
			}
			Markers.Set(SERVER_KEY, data.param1);
			m_BasicMapConfig = data.param2;
		} else if (GetGame().IsMultiplayer() && GetGame().IsServer()){
			if (Markers.Get(SERVER_KEY)){
				ServerMarkers = Markers.Get(SERVER_KEY);
			}
			//Print("[BASICMAP]Sending " + ServerMarkers.Count() + " Server Markers" );
			GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param2< array<ref BasicMapMarker>, ref BasicMapConfig>( ServerMarkers, GetBasicMapConfig() ), true, sender);
		}
	} 
	
	void LoadServerMarkers(){
		array<ref BasicMapMarker> ServerMarkers;
		JsonFileLoader< array<ref BasicMapMarker> >.JsonLoadFile(BasicMapPath + ServerMarkersPath, ServerMarkers);
		if (ServerMarkers){
			for ( int i = 0; i < ServerMarkers.Count(); i++){
				vector pos = ServerMarkers.Get(i).GetPosition();
				if ( pos[1] == 0){
					pos[1] = GetGame().SurfaceY( pos[0], pos[2] );
					ServerMarkers.Get(i).SetPosition(pos);
				}
				ServerMarkers.Get(i).SetCanEdit(false);
				ServerMarkers.Get(i).SetGroup(SERVER_KEY);
			}
			Markers.Set(SERVER_KEY, ServerMarkers);
		}
	}
	
	void ServerFirstRun(){
		array<ref BasicMapMarker> ServerMarkers = new array<ref BasicMapMarker>;
		ServerMarkers.Insert(new ref BasicMapMarker("GREEN MOUNTAIN", Vector(3693.56, 402.312,6010.05), "BasicMap\\gui\\images\\marker.paa", {212, 138, 251}, 240, true));
		ServerMarkers.Insert(new ref BasicMapMarker("KUMYRNA", Vector(8345.61, 292.302, 5985.93), "BasicMap\\gui\\images\\marker.paa", {212, 138, 251}, 240, true));
		for (int i = 0; i < ServerMarkers.Count(); i++){
			ServerMarkers.Get(i).SetCanEdit(false);
			ServerMarkers.Get(i).SetGroup(SERVER_KEY);
			//ServerMarkers.Get(i).PrintDebug();
		}
		Markers.Set(SERVER_KEY, ServerMarkers);
		JsonFileLoader< array<ref BasicMapMarker> >.JsonSaveFile(BasicMapPath + ServerMarkersPath, ServerMarkers);
	}

	
	void LoadClientMarkers(){
		string server;
        GetCLIParam("connect", server);
		string clientPath = BasicMapPath + "\\" + server + ".json";
		if (FileExist(clientPath)){
			array<ref BasicMapMarker> ClientMarkers;
			JsonFileLoader< array<ref BasicMapMarker> >.JsonLoadFile(clientPath, ClientMarkers);
			for (int i = 0; i < ClientMarkers.Count(); i++){
				ClientMarkers.Get(i).SetGroup(CLIENT_KEY);
				ClientMarkers.Get(i).SetCanEdit(true);
				//ClientMarkers.Get(i).PrintDebug();
			}
			if (!ClientMarkers){
				ClientMarkers = new array<ref BasicMapMarker>;
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
	
	ref array<ref BasicMapMarker> GetMarkers(string id){
		return Markers.Get(id);
	}
	
	void AddMarker(string groupId, ref BasicMapMarker marker){
		if (Markers.Get(groupId)){
			marker.SetGroup(groupId);
			OnMarkerSave(marker);
			Markers.Get(groupId).Insert(marker);
		} else {
			ref array<ref BasicMapMarker> markers = new ref array<ref BasicMapMarker>;
			marker.SetGroup(groupId);
			markers.Insert(marker);
			OnMarkerSave(marker);
			Markers.Insert(groupId, markers);
		}
	}
	
	void CreateMarker(string group, string name, vector pos, bool overrideSettings = false){
		if (Factories.Get(group) && Groups.Get(group) && (Groups.Get(group).Creatable() || overrideSettings)){
			AddMarker(group, Factories.Get(group).Create(name, pos));
		} else {
			AddMarker(CLIENT_KEY, Factories.Get(CLIENT_KEY).Create(name, pos));
		}
	}
	
	void ChangeGroups(string from, string to, ref BasicMapMarker marker){
		if (Markers.Get(to)){
			Markers.Get(from).Insert(marker);
		}
		
		if (Markers.Get(from)){
			int index = Markers.Get(from).Find(marker);
			if (index >= 0){
				Markers.Get(from).RemoveOrdered(index);
			}
		}	 
	}
	
	void SetMarkers(string groupId, ref array<ref BasicMapMarker> markers){
		if (Markers.Get(groupId)){
			Markers.Set(groupId, markers);
		} else {
			Markers.Insert(groupId, markers);
		}
	}
	
	void RemoveAllMarkers(string key){
		if (Markers.Get(key)){
			Markers.Remove(key);
		}
	}
	
	void RemoveMarker(string key, ref BasicMapMarker marker){
		if (Markers.Get(key)){ 
			OnMarkerDelete(marker);
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(Markers.Get(key).RemoveItem, marker);
		}
	}
	
	bool RemoveMarker(ref BasicMapMarker marker){
		for (int j = 0; j < Markers.Count(); j++){
			for (int k = 0; k < Markers.GetElement(j).Count(); k++){
				if (marker == Markers.GetElement(j).Get(k)){
					OnMarkerDelete(marker); 
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(Markers.GetElement(j).RemoveOrdered, k);
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
	
	ref BasicMapMarker GetMarkerByVector(vector pos, float distance = 10, bool overrideSettings = false){
		for (int j = 0; j < Markers.Count(); j++){
			for (int k = 0; k < Markers.GetElement(j).Count(); k++){
				if (vector.Distance(Markers.GetElement(j).Get(k).GetPosition(), pos) < distance && (Markers.GetElement(j).Get(k).Editable() || overrideSettings)){
					Markers.GetElement(j).Get(k).SetGroup(Markers.GetKey(j));
					return Markers.GetElement(j).Get(k);
				}
			}
		}
		return NULL;
	}

	bool RemoveMarkerByVector(vector pos, float distance = 10, bool overrideSettings = false){
		for (int j = 0; j < Markers.Count(); j++){
			for (int k = 0; k < Markers.GetElement(j).Count(); k++){
				if (vector.Distance(Markers.GetElement(j).Get(k).GetPosition(), pos) < distance && (Markers.GetElement(j).Get(k).Editable() || overrideSettings)){
					OnMarkerDelete(Markers.GetElement(j).Get(k));
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(Markers.GetElement(j).RemoveOrdered, k); //So that way OnMarkerDelete is called before the delete encase this is the last ref
					return true;
				}
			}
		}
		return false;
	}
	
	static string GetInfoText(){
		if (GetBasicMapConfig().AllowPlayerMarkers){
			return InfoText;
		}
		return "";
	}
	
	
	//Markers are updated live this is more just on marker editor close or marker created
	void OnMarkerSave(ref BasicMapMarker marker){
		
	}
	
	void OnMarkerDelete(ref BasicMapMarker marker){
	
	}
	
	void SetMarkersOnHUD(bool onHUD){
		MarkersOnHUD = onHUD;
	}
	
	void ToggleMarkersOnHUD(){
		MarkersOnHUD = !MarkersOnHUD;
	}
	
	bool ShowMarkersOnHUD(){
		return MarkersOnHUD && GetBasicMapConfig().Allow3dMarkers;
	}
	
	bool ShouldShowOnHUD(string group){
		if (Groups.Get(group)){
			return Groups.Get(group).OnHUD();
		} 
		return false;
	}
	
	bool ShouldShowOnMap(string group){
		if (Groups.Get(group)){
			return Groups.Get(group).OnMap();
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