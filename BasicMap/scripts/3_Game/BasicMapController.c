class BasicMapController extends Managed{
	bool IsInit = false;
	EntityAI MapItem = NULL;
	
	static string ServerMarkersPath = "\\ServerMarkers.json";
	static string CircleMarkersPath = "\\ServerCircleMarkers.json";
	static string BasicMapPath = "$profile:BasicMap";
	
	protected bool MarkersOnHUD = true;
	
	static string SERVER_KEY = "BASICMAP_SERVER";
	static string CLIENT_KEY = "BASICMAP_CLIENT";
	
	static string PARTY_KEY = "";
	
	static string InfoText = "<p>Double Left-Click to Create Marker</p><p>Double Right-Click to Delete Marker</p>";
		
	autoptr map< string, autoptr array<autoptr BasicMapMarker> > Markers = new map< string, autoptr array<autoptr BasicMapMarker> >;
	
	//GROUP NAME DISPLAYNAME? or MetaDataObject?
	autoptr map< string, autoptr BasicMapGroupMetaData> Groups = new map<string, autoptr BasicMapGroupMetaData>;
	autoptr map<string, autoptr BasicMapMarkerFactory> Factories = new map<string, autoptr BasicMapMarkerFactory>;
	
	void Init(){
		if (!IsInit){
			IsInit = true;
			GetRPCManager().AddRPC( "BasicMap", "RPCSyncServerData", this, SingeplayerExecutionType.Both );
			GetRPCManager().AddRPC( "BasicMap", "RPCSyncGroupData", this, SingeplayerExecutionType.Both );
			
			
			RegisterGroup(SERVER_KEY, new BasicMapGroupMetaData(SERVER_KEY, "SERVER MARKERS"), NULL);
			RegisterGroup(CLIENT_KEY, new BasicMapGroupMetaData(CLIENT_KEY, "PERSONAL MARKERS", true), new BasicMapMarkerFactory());
		}
		if (GetGame().IsMultiplayer() && GetGame().IsClient()){
			Print("[BasicMap] Init Client");
			GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param3< array<autoptr BasicMapMarker>, array<autoptr BasicMapCircleMarker>, BasicMapConfig >( NULL, NULL, NULL ), true, NULL);
			LoadClientMarkers();
		} else {
			Print("[BasicMap] Init Server");
			if (!FileExist(BasicMapPath + ServerMarkersPath)){
				MakeDirectory(BasicMapPath);
				ServerFirstRun();
			} else {
				 LoadServerMarkers();
			}
			if (FileExist(BasicMapPath + CircleMarkersPath)){
				LoadServerCircleMarkers();
			}
		}
	}
	
	void SetMapItem( EntityAI mapItem){
		MapItem = EntityAI.Cast(mapItem);
	}
	
	EntityAI GetMapItem(){
		return MapItem;
	}
	
	void OnMapClose(){
		SaveClientMarkers();
		if (MapItem && GetBasicMapConfig().SaveMarkersToMapItem){
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.ClearMapItem, 150,false);
		}
	}
	
	void ClearMapItem(){
		MapItem = NULL;
	}
	
	
	map< string, autoptr BasicMapGroupMetaData> GetGroups(){
		return Groups;
	}
	
	
	BasicMapGroupMetaData GetGroup(string id){
		return Groups.Get(id);
	}
	
	
	string GetGroupName(string id){
		return Groups.Get(id).GetDisplayName();
	}
	
	
	void RegisterGroup(string id, BasicMapGroupMetaData metaData, BasicMapMarkerFactory factory){
		Groups.Insert(id, metaData);
		Factories.Insert(id, factory);
	}
	

	void RPCSyncGroupData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ){
		Param3<string, array<autoptr BasicMapMarker>, array<autoptr BasicMapCircleMarker>> data;
		int i;
		if ( !ctx.Read( data ) ) return;
		string group = data.param1;
		//Print("[BasicMap] RPCSyncGroupData " + group );
        if ( data.param2 || data.param3){
			array<autoptr BasicMapMarker> inMarkers = data.param2;
			inMarkers.Debug();
			
			array<autoptr BasicMapCircleMarker> inCMarkers = data.param3;
			inCMarkers.Debug();
			
			array<autoptr BasicMapMarker> markers = new array<autoptr BasicMapMarker>;
			if (inMarkers){
				for ( i = 0; i < inMarkers.Count(); i++){
					if (inMarkers.Get(i)){
						inMarkers.Get(i).SetGroup(group);
						markers.Insert(inMarkers.Get(i));
					}
				}
			}
			if (inCMarkers){
				for ( i = 0; i < inCMarkers.Count(); i++){
					if (inCMarkers.Get(i)){
						inCMarkers.Get(i).SetGroup(group);
						markers.Insert(inCMarkers.Get(i));
					}
				}
			}
			//Print("Markers: " + group);
			markers.Debug();
			SetMarkers(group, markers);
		} else if (!data.param2 && !data.param3 && GetGame().IsServer() && sender){//Is requesting
			//Print("Player Requested Update: " + group);
			UpdateGroupRemote(group, sender);
		}
	}
	
	void RPCSyncServerData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ){
		Param3< array<autoptr BasicMapMarker>, array<autoptr BasicMapCircleMarker>, ref BasicMapConfig> data;
		array<autoptr BasicMapMarker> ServerMarkers = new array<autoptr BasicMapMarker>;
		array<autoptr BasicMapCircleMarker> ServerCircleMarkers = new array<autoptr BasicMapCircleMarker>;
		if ( !ctx.Read( data ) ) return;
        if ( GetGame().IsMultiplayer() && GetGame().IsClient() ){
			ServerMarkers =  data.param1;
			ServerCircleMarkers =  data.param2;
			for ( int i = 0; i < ServerMarkers.Count(); i++){
				ServerMarkers.Get(i).SetCanEdit(false);
				ServerMarkers.Get(i).SetGroup(SERVER_KEY);
			}
			for ( i = 0; i < ServerCircleMarkers.Count(); i++){
				ServerCircleMarkers.Get(i).SetCanEdit(false);
				ServerCircleMarkers.Get(i).SetGroup(SERVER_KEY);
				ServerMarkers.Insert(ServerCircleMarkers.Get(i));
			}
			Markers.Set(SERVER_KEY, ServerMarkers);
			m_BasicMapConfig = data.param3;
		} else if (GetGame().IsMultiplayer() && GetGame().IsServer()){
			if (Markers.Get(SERVER_KEY)){
				BasicMapCircleMarker cMarker;
				for ( int j = 0; j < Markers.Get(SERVER_KEY).Count(); j++){
					if (Markers.Get(SERVER_KEY).Get(j).IsInherited(BasicMapCircleMarker) && Class.CastTo(cMarker, Markers.Get(SERVER_KEY).Get(j)) && cMarker.GetRadius() > 0){
						ServerCircleMarkers.Insert(cMarker);
					} else {
						ServerMarkers.Insert(Markers.Get(SERVER_KEY).Get(j));
					}
				}
			}
			GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param3< array<autoptr BasicMapMarker>,  array<autoptr BasicMapCircleMarker>, ref BasicMapConfig>( ServerMarkers, ServerCircleMarkers, GetBasicMapConfig() ), true, sender);
		}
	}
	
	void LoadServerMarkers(){
		array<autoptr BasicMapMarker> ServerMarkers;
		JsonFileLoader< array<autoptr BasicMapMarker> >.JsonLoadFile(BasicMapPath + ServerMarkersPath, ServerMarkers);
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
		array<autoptr BasicMapMarker> ServerMarkers = new array<autoptr BasicMapMarker>;
		ServerMarkers.Insert(new BasicMapMarker("GREEN MOUNTAIN", Vector(3693.56, 402.312,6010.05), "BasicMap\\gui\\images\\marker.paa", {212, 138, 251}, 240, true));
		ServerMarkers.Insert(new BasicMapMarker("KUMYRNA", Vector(8345.61, 292.302, 5985.93), "BasicMap\\gui\\images\\marker.paa", {212, 138, 251}, 240, true));
		for (int i = 0; i < ServerMarkers.Count(); i++){
			ServerMarkers.Get(i).SetCanEdit(false);
			ServerMarkers.Get(i).SetGroup(SERVER_KEY);
			//ServerMarkers.Get(i).PrintDebug();
		}
		Markers.Set(SERVER_KEY, ServerMarkers);
		JsonFileLoader< array<autoptr BasicMapMarker> >.JsonSaveFile(BasicMapPath + ServerMarkersPath, ServerMarkers);
	}

	
	void LoadClientMarkers(){
		if (GetBasicMapConfig().SaveMarkersToMapItem){
			Markers.Set(CLIENT_KEY, new array<autoptr BasicMapMarker>);
			return;
		}
		string server;
        GetCLIParam("connect", server);
		string clientPath = BasicMapPath + "\\" + server + ".json";
		if (FileExist(clientPath)){
			array<autoptr BasicMapMarker> ClientMarkers;
			JsonFileLoader< array<autoptr BasicMapMarker> >.JsonLoadFile(clientPath, ClientMarkers);
			for (int i = 0; i < ClientMarkers.Count(); i++){
				ClientMarkers.Get(i).SetGroup(CLIENT_KEY);
				ClientMarkers.Get(i).SetCanEdit(true);
				//ClientMarkers.Get(i).PrintDebug();
			}
			if (!ClientMarkers){
				ClientMarkers = new array<autoptr BasicMapMarker>;
			}
			Markers.Set(CLIENT_KEY, ClientMarkers);
		} else {
			MakeDirectory(BasicMapPath);
			SaveClientMarkers();
		}
	}
	
	void SaveClientMarkers(){
		array<autoptr BasicMapMarker> ClientMarkers = new array<autoptr BasicMapMarker>;
		if (Markers.Get(CLIENT_KEY)){
			ClientMarkers = array<autoptr BasicMapMarker>.Cast(Markers.Get(CLIENT_KEY));
		}
		if (MapItem && GetBasicMapConfig().SaveMarkersToMapItem){
			GetGame().RPCSingleParam(MapItem, BASICMAPRPCs.SAVE_MARKERS, new Param1<array<autoptr BasicMapMarker>>(ClientMarkers), true, NULL);
		} else {
			string server;
       	 	GetCLIParam("connect", server);
			string clientPath = BasicMapPath + "\\" + server + ".json";
			JsonFileLoader< array<autoptr BasicMapMarker> >.JsonSaveFile(clientPath, ClientMarkers);
		}
	}
	
	void LoadServerCircleMarkers(){
		array<autoptr BasicMapCircleMarker> CircleMarkers;
		JsonFileLoader< array<autoptr BasicMapCircleMarker> >.JsonLoadFile(BasicMapPath + CircleMarkersPath, CircleMarkers);
		if (CircleMarkers){
			for ( int i = 0; i < CircleMarkers.Count(); i++){
				vector pos = CircleMarkers.Get(i).GetPosition();
				if ( pos[1] == 0){
					pos[1] = GetGame().SurfaceY( pos[0], pos[2] );
					CircleMarkers.Get(i).SetPosition(pos);
				}
				CircleMarkers.Get(i).SetCanEdit(false);
				CircleMarkers.Get(i).SetGroup(SERVER_KEY);
				//CircleMarkers.Get(i).PrintDebug();
				AddMarker(SERVER_KEY, CircleMarkers.Get(i));
			}
		}
		
	}
	
	BasicMapMarker Marker(int i){
		for (int j = 0; j < Markers.Count(); j++){
			int nextIndex = Markers.GetElement(j).Count();
			if (i < nextIndex){
				return BasicMapMarker.Cast(Markers.GetElement(j).Get(i));
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
	
	array<autoptr BasicMapMarker> GetMarkers(string id){
		if (id == ""){
			return NULL;
		}
		return Markers.Get(id);
	}
	
	void AddMarker(string groupId, BasicMapMarker marker){
		if (Markers.Get(groupId)){
			marker.SetGroup(groupId);
			OnMarkerSave(marker);
			Markers.Get(groupId).Insert(marker);
		} else {
			array<autoptr BasicMapMarker> markers = new array<autoptr BasicMapMarker>;
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
	
	void SetMarkers(string groupId, array<autoptr BasicMapMarker> markers){
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
	
	void RemoveMarker(string key, BasicMapMarker marker){
		if (Markers.Get(key)){ 
			OnMarkerDelete(marker);
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(Markers.Get(key).RemoveItem, marker);
		}
	}
	
	bool RemoveMarker(BasicMapMarker marker){
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
	
	array<autoptr BasicMapMarker> ClientMarkers(){
		return Markers.Get(CLIENT_KEY);
	}
	
	int AddClientMarker(BasicMapMarker marker){
		if ( Markers.Get(CLIENT_KEY)){
			marker.SetCanEdit(true);
			marker.SetGroup(CLIENT_KEY);
			return Markers.Get(CLIENT_KEY).Insert(marker);
		}
		return -1;
	}
	
	BasicMapMarker ClientMarker(int i){
		if ( Markers.Get(CLIENT_KEY)){
			return BasicMapMarker.Cast(Markers.Get(CLIENT_KEY).Get(i));
		}
		return NULL;
	}
	
	BasicMapMarker GetMarkerByVector(vector pos, float distance = 10, bool overrideSettings = false){
		for (int j = 0; j < Markers.Count(); j++){
			for (int k = 0; k < Markers.GetElement(j).Count(); k++){
				if (vector.Distance(Markers.GetElement(j).Get(k).GetPosition(), pos) < distance && (Markers.GetElement(j).Get(k).Editable() || overrideSettings)){
					Markers.GetElement(j).Get(k).SetGroup(Markers.GetKey(j));
					return BasicMapMarker.Cast(Markers.GetElement(j).Get(k));
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
	
	
	void SetMarkersRemote(string group, array<autoptr BasicMapMarker> markers, PlayerIdentity toPlayer = NULL ){
		//Print("[BasicMap] SetMarkersRemote " + group );
		array<autoptr BasicMapMarker>  basicMarkers = new array<autoptr BasicMapMarker>;
		array<autoptr BasicMapCircleMarker> circleMarkers = new array<autoptr BasicMapCircleMarker>;
		BasicMapCircleMarker cMarker;
		for ( int j = 0; j < markers.Count(); j++){
			if (markers.Get(j).IsInherited(BasicMapCircleMarker) && Class.CastTo(cMarker, markers.Get(j)) && cMarker.GetRadius() > 0){
				circleMarkers.Insert(cMarker);
			} else {
				basicMarkers.Insert(markers.Get(j));
			}
		}
		GetRPCManager().SendRPC("BasicMap", "RPCSyncGroupData", new Param3<string, array<autoptr BasicMapMarker>, array<autoptr BasicMapCircleMarker> >( group, basicMarkers, circleMarkers ), true, toPlayer);
	}
	
	void UpdateGroupRemote(string group, PlayerIdentity toPlayer = NULL ){
		//Print("[BasicMap] UpdateGroupRemote " + group );
		SetMarkersRemote("BasicMap", GetMarkers(group), toPlayer);
	}
	
	void RequestGroupUpdate(string group){
		if (GetGame().IsServer()){
			Error("[BasicMap] !!!!!! BAD USSAGE !!!!!! --  Trying to request Group Update from server shouldn't do this as it will essentially get every player to update the server causing no consistancy");
			return;
		}
		GetRPCManager().SendRPC("BasicMap", "RPCSyncGroupData", new Param3<string, array<autoptr BasicMapMarker>, array<autoptr BasicMapCircleMarker> >( group, NULL, NULL ), true);
	}
	
	static string GetInfoText(){
		if (GetBasicMapConfig().AllowPlayerMarkers){
			return InfoText;
		}
		return "";
	}
	
	
	//Markers are updated live this is more just on marker editor close or marker created
	void OnMarkerSave(ref BasicMapMarker marker){
		if (marker.GetGroup() == this.CLIENT_KEY){
			SaveClientMarkers();
		}
	}
	
	void OnMarkerDelete(ref BasicMapMarker marker){
		if (marker.GetGroup() == this.CLIENT_KEY){
			SaveClientMarkers();
		}
	
	}
	
	void SetMarkersOnHUD(bool onHUD){
		MarkersOnHUD = onHUD;
	}
	
	void ToggleMarkersOnHUD(){
		MarkersOnHUD = !MarkersOnHUD;
	}
	
	bool ShowMarkersOnHUD(){
		if ( GetBasicMapConfig().RequireCompassToSee3d && GetGame().IsClient() ){
			DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());

            if (player){
				array<EntityAI> itemsArray = new array<EntityAI>;
				player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);    	
                for (int i = 0; i < itemsArray.Count(); i++){
                    if (itemsArray.Get(i)){ 
						string itemType = itemsArray.Get(i).GetType();
						itemType.ToLower();
						if (itemType.Contains("compass")){
							return MarkersOnHUD && GetBasicMapConfig().Allow3dMarkers;
						}
                    }
                }
            }
			return false;
		}
		return MarkersOnHUD && GetBasicMapConfig().Allow3dMarkers;
	}
	
	bool ShouldShowOnHUD(string group){
		if (Groups.Get(group)){
			return Groups.Get(group).OnHUD();
		} 
		return true;
	}
	
	bool ShouldShowOnMap(string group) {
		if (Groups.Get(group)){
			return Groups.Get(group).OnMap();
		} 
		return true;
	}
	
	bool ShowSelfOnMap(){
		if ( GetBasicMapConfig().RequireCompassToSeeSelf && GetGame().IsClient() ){
			DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());

            if (player){
				array<EntityAI> itemsArray = new array<EntityAI>;
				player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);    	
                for (int i = 0; i < itemsArray.Count(); i++){
                    if (itemsArray.Get(i)){ 
						string itemType = itemsArray.Get(i).GetType();
						itemType.ToLower();
						if (itemType.Contains("compass")){
                            return true;
						}
                    }
                }
            }
			return false;
		} 
		return GetBasicMapConfig().ShowSelfOnMap;
	}
}


ref BasicMapController m_BasicMapController;

static BasicMapController BasicMap(){
	if (!m_BasicMapController){
		m_BasicMapController = new BasicMapController;
	}
	return m_BasicMapController;
}