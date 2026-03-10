class BasicMapController extends Managed{
	bool IsInit = false;
	EntityAI MapItem = NULL;
	
	static string ServerMarkersPath = "\\ServerMarkers.json";
	static string CircleMarkersPath = "\\ServerCircleMarkers.json";
	static string BasicMapPath = "$profile:BasicMap";
	
	protected bool MarkersOnHUD = true;
	
	// Set true when markers are replaced/added/removed so HUD can rebuild
	bool m_MarkersDirty = false;
	
	// Marker visibility mode for K key cycling
	protected int m_VisibilityMode = BasicMapVisibilityMode.SHOW_ALL;
	
	static string SERVER_KEY = "BASICMAP_SERVER";
	static string CLIENT_KEY = "BASICMAP_CLIENT";
	
	static string PARTY_KEY = "";
	
	static string InfoText = "Single Click to Edit  |  Double Left-Click to Create  |  Double Right-Click to Delete";
		
	autoptr map< string, autoptr array<autoptr BasicMapMarker> > Markers = new map< string, autoptr array<autoptr BasicMapMarker> >;
	
	//GROUP NAME DISPLAYNAME? or MetaDataObject?
	autoptr map< string, autoptr BasicMapGroupMetaData> Groups = new map<string, autoptr BasicMapGroupMetaData>;
	autoptr map<string, autoptr BasicMapMarkerFactory> Factories = new map<string, autoptr BasicMapMarkerFactory>;
	
	protected vector LastLookedAtPos = vector.Zero;
	protected float LastLookedAtZoom = -1;
	
	// ---- Inventory item cache (avoids repeated EnumerateInventory scans) ----
	protected float m_InvCacheTime = -1;       // Time of last cache refresh
	protected static float INV_CACHE_TTL = 1.0; // Cache valid for 1 second
	protected bool m_CachedHasCompass = false;
	protected bool m_CachedHasPen = false;
	protected bool m_CachedHasSelfItem = false; // compass/navigator for ShowSelfOnMap
	protected bool m_CachedHasMapItem = false;
	protected bool m_CachedHasGPS = false;      // GPS/Navigator with power (for NavHUD)
	
	// Refresh inventory cache if stale. Called once per frame at most.
	void RefreshInventoryCache(){
		float now = GetGame().GetTickTime();
		if (m_InvCacheTime >= 0 && (now - m_InvCacheTime) < INV_CACHE_TTL){
			return; // Cache still valid
		}
		m_InvCacheTime = now;
		m_CachedHasCompass = false;
		m_CachedHasPen = false;
		m_CachedHasSelfItem = false;
		m_CachedHasMapItem = false;
		m_CachedHasGPS = false;
		
		if (!GetGame().IsClient()){
			return;
		}
		DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());
		if (!player || !player.GetInventory()){
			return;
		}
		
		string requiredSelfItem = GetBasicMapConfig().ItemRequiredToSeeSelf;
		requiredSelfItem.ToLower();
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++){
			EntityAI item;
			if (!Class.CastTo(item, itemsArray.Get(i))){
				continue;
			}
			string itemType = item.GetType();
			itemType.ToLower();
			
			if (itemType.Contains("compass") != -1 && !item.IsRuined()){
				m_CachedHasCompass = true;
			}
			if (itemType.Contains("pen_") != -1){
				m_CachedHasPen = true;
			}
			if ((itemType.Contains("gps") != -1 || itemType.Contains("navigator") != -1) && item.GetCompEM() && item.GetCompEM().IsSwitchedOn() && item.GetCompEM().IsWorking()){
				m_CachedHasGPS = true;
			}
			if (itemType.Contains(requiredSelfItem) != -1){
				// Self-item may require power (compass/navigator)
				if (!item.GetCompEM() || (item.GetCompEM().IsSwitchedOn() && item.GetCompEM().IsWorking())){
					m_CachedHasSelfItem = true;
				}
			}
			if (item.IsKindOf("ItemMap")){
				m_CachedHasMapItem = true;
			}
		}
	}
	
	bool HasCachedCompass(){
		RefreshInventoryCache();
		return m_CachedHasCompass;
	}
	
	bool HasCachedPen(){
		RefreshInventoryCache();
		return m_CachedHasPen;
	}
	
	bool HasCachedSelfItem(){
		RefreshInventoryCache();
		return m_CachedHasSelfItem;
	}
	
	bool HasCachedMapItem(){
		RefreshInventoryCache();
		return m_CachedHasMapItem;
	}
	
	bool HasCachedGPS(){
		RefreshInventoryCache();
		return m_CachedHasGPS;
	}
	
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
	
	void SetLastLook(vector pos, float zoom){
		LastLookedAtPos = pos;
		LastLookedAtZoom = zoom;
	}
	
	bool GetLastLook(out vector pos, out float zoom){
		if (LastLookedAtPos != vector.Zero && LastLookedAtZoom != -1){
			pos = LastLookedAtPos;
			zoom = LastLookedAtZoom;
			return true;
		}
		return false;
		
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
	

	void RPCSyncGroupData( CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target ){
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
	
	void RPCSyncServerData( CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target ){
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
		array<autoptr BasicMapMarker> ClientMarkers;
		if (Markers.Get(CLIENT_KEY)){
			ClientMarkers = array<autoptr BasicMapMarker>.Cast(Markers.Get(CLIENT_KEY));
		}
		if (!ClientMarkers){
			ClientMarkers = new array<autoptr BasicMapMarker>;
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
	
	// Returns a flat array of ALL markers across all groups.
	// Use this for bulk iteration instead of repeated Marker(i) calls,
	// which is O(n) per call making loops O(n²).
	array<BasicMapMarker> GetAllMarkers(){
		array<BasicMapMarker> all = new array<BasicMapMarker>;
		for (int j = 0; j < Markers.Count(); j++){
			array<autoptr BasicMapMarker> group = Markers.GetElement(j);
			for (int k = 0; k < group.Count(); k++){
				BasicMapMarker m = BasicMapMarker.Cast(group.Get(k));
				if (m){
					all.Insert(m);
				}
			}
		}
		return all;
	}
	
	array<autoptr BasicMapMarker> GetMarkers(string id){
		if (id == ""){
			return NULL;
		}
		return Markers.Get(id);
	}
	
	void AddMarker(string groupId, BasicMapMarker marker){
		marker.SetGroup(groupId);
		OnMarkerSave(marker);
		if (!Markers.Get(groupId)){
			Markers.Insert(groupId, new array<autoptr BasicMapMarker>);
		}
		Markers.Get(groupId).Insert(marker);
	}
	
	void CreateMarker(string group, string name, vector pos, bool overrideSettings = false){
		if (Factories.Get(group) && Groups.Get(group) && (Groups.Get(group).Creatable() || overrideSettings)){
			AddMarker(group, Factories.Get(group).Create(name, pos));
		} else {
			AddMarker(CLIENT_KEY, Factories.Get(CLIENT_KEY).Create(name, pos));
		}
	}
	
	void ChangeGroups(string from, string to, BasicMapMarker marker){
		// Insert into target BEFORE removing from source.
		// The source array holds an autoptr to the marker. Removing it first
		// could delete the marker (if it's the last strong ref) before we can
		// insert it into the target array.
		if (Markers.Get(to)){
			Markers.Get(to).Insert(marker);
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
		m_MarkersDirty = true;
	}
	
	void RemoveAllMarkers(string key){
		if (Markers.Get(key)){
			Markers.Remove(key);
		}
		m_MarkersDirty = true;
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
		SetMarkersRemote(group, GetMarkers(group), toPlayer);
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
	void OnMarkerSave(BasicMapMarker marker){
		if (marker.GetGroup() == this.CLIENT_KEY){
			SaveClientMarkers();
		}
	}
	
	void OnMarkerDelete(BasicMapMarker marker){
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
	
	// Get current visibility mode
	int GetVisibilityMode(){
		return m_VisibilityMode;
	}
	
	// Set visibility mode directly
	void SetVisibilityMode(int mode){
		m_VisibilityMode = mode;
		if (mode == BasicMapVisibilityMode.HIDE_ALL){
			MarkersOnHUD = false;
		} else {
			MarkersOnHUD = true;
		}
	}
	
	// Cycle to next visibility mode: Show All -> Server Only -> Local Only -> Hide All -> Show All
	void CycleVisibilityMode(){
		int mode = m_VisibilityMode + 1;
		if (mode > BasicMapVisibilityMode.HIDE_ALL){
			mode = BasicMapVisibilityMode.SHOW_ALL;
		}
		SetVisibilityMode(mode);
	}
	
	// Quick toggle between Show All and Hide All (for long press)
	void QuickToggleVisibility(){
		if (m_VisibilityMode == BasicMapVisibilityMode.HIDE_ALL){
			SetVisibilityMode(BasicMapVisibilityMode.SHOW_ALL);
		} else {
			SetVisibilityMode(BasicMapVisibilityMode.HIDE_ALL);
		}
	}
	
	// Get display name for current visibility mode
	string GetVisibilityModeName(){
		switch (m_VisibilityMode){
			case BasicMapVisibilityMode.SHOW_ALL:
				return "All Markers";
			case BasicMapVisibilityMode.SERVER_ONLY:
				return "Server Markers Only";
			case BasicMapVisibilityMode.LOCAL_ONLY:
				return "Personal Markers Only";
			case BasicMapVisibilityMode.HIDE_ALL:
				return "Markers Hidden";
		}
		return "Unknown";
	}
	
	bool ShowMarkersOnHUD(){
		if ( GetBasicMapConfig().RequireCompassToSee3d && GetGame().IsClient() ){
			if (!HasCachedCompass()){
				return false;
			}
		}
		return MarkersOnHUD && GetBasicMapConfig().Allow3dMarkers;
	}
	
	bool ShouldShowOnHUD(string group){
		// Check visibility mode filter first
		switch (m_VisibilityMode){
			case BasicMapVisibilityMode.HIDE_ALL:
				return false;
			case BasicMapVisibilityMode.SERVER_ONLY:
				if (group != SERVER_KEY){
					return false;
				}
				break;
			case BasicMapVisibilityMode.LOCAL_ONLY:
				if (group == SERVER_KEY){
					return false;
				}
				break;
			// SHOW_ALL falls through to normal group check
		}
		
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
			return HasCachedSelfItem();
		} 
		return GetBasicMapConfig().ShowSelfOnMap;
	}
}


static ref BasicMapController m_BasicMapController;

static BasicMapController BasicMap(){
	if (!m_BasicMapController){
		m_BasicMapController = new BasicMapController;
	}
	return m_BasicMapController;
}