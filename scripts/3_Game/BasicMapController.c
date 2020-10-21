class BasicMapController{
	static string ServerMarkersPath = "$profile:BasicMap\\ServerMarkers.json";
	static string ClientMarkersPath = "$profile:BasicMap\\ClientMarkers.json";
	ref array<ref BasicMapMarker> ServerMarkers = new ref array<ref BasicMapMarker>;
	
	ref array<ref BasicMapMarker> ClientMarkers = new ref array<ref BasicMapMarker>;
	
	ref map< string, ref BasicMapMarker > ModMarkers = new ref map< string, ref BasicMapMarker >;
	
	void Init(){
		GetRPCManager().AddRPC( "BasicMap", "RPCSyncServerData", this, SingeplayerExecutionType.Both );
		if (GetGame().IsMultiplayer() && GetGame().IsClient()){
			GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param1< array<ref BasicMapMarker> >( NULL ), true, NULL);
		} else {
			if (!FileExist(ServerMarkersPath)){
				MakeDirectory("$profile:BasicMap");
				ServerFirstRun();
			} else {
				 LoadServerMarkers();
			}
		}
	}
	
	void RPCSyncServerData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ){
		Param1< array<ref BasicMapMarker> > data;
		if ( !ctx.Read( data ) ) return;
        if ( GetGame().IsMultiplayer() && GetGame().IsClient() ){
			ServerMarkers = data.param1;
			Print("[BASICMAP]Loading " + ServerMarkers.Count() + " Server Markers" );
		} else if (GetGame().IsMultiplayer() && GetGame().IsServer()){
			Print("[BASICMAP]Sending " + ServerMarkers.Count() + " Server Markers" );
			GetRPCManager().SendRPC("BasicMap", "RPCSyncServerData", new Param1< array<ref BasicMapMarker> >( ServerMarkers ), true, sender);
		}
	} 
	
	void LoadServerMarkers(){
		JsonFileLoader< array<ref BasicMapMarker> >.JsonLoadFile(ServerMarkersPath, ServerMarkers);
	}
	
	void ServerFirstRun(){
		ServerMarkers.Insert(new ref BasicMapMarker("GREEN MOUNTAIN", "BasicMap\\gui\\images\\marker.paa", Vector(3693.56, 402.312,6010.05), {212, 138, 251}));
		ServerMarkers.Insert(new ref BasicMapMarker("KUMYRNA", "BasicMap\\gui\\images\\marker.paa", Vector(8345.61, 292.302, 5985.93), {212, 138, 251}));
		JsonFileLoader< array<ref BasicMapMarker> >.JsonSaveFile(ServerMarkersPath, ServerMarkers);
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
			return ModMarkers.GetElement(i);
		}
		return NULL;
	}
	
	int Count(){
		return ServerMarkers.Count() + ClientMarkers.Count() + ModMarkers.Count();
	}
	
	ref BasicMapMarker ModMarker(string mod, string key){
		return ModMarkers.Get(mod+key);
	}
	
	void AddMarker(string mod, string key, ref BasicMapMarker marker){
		if (ModMarkers.Get(mod+key)){
			ModMarkers.Set(mod+key, marker);
		} else {
			ModMarkers.Insert(mod+key, marker);
		}
	}
	
	int AddClientMarker(ref BasicMapMarker marker){
		return ClientMarkers.Insert(marker);
	}
	
	ref BasicMapMarker ClientMarker(int i){
		return ClientMarkers.Get(i);
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