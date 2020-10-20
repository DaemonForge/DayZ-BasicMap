class BasicMapController{
	static string ServerMarkersPath = "$profile:BasicMap\\ServerMarkers.json";
	static string ClientMarkersPath = "$profile:BasicMap\\ClientMarkers.json";
	ref array<ref BasicMapMarker> ServerMarkers = new ref array<ref BasicMapMarker>;
	ref array<ref BasicMapMarker> ClientMarkers = new ref array<ref BasicMapMarker>;
	ref array<ref BasicMapMarker> GroupMarkers = new ref array<ref BasicMapMarker>;
	
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
		ServerMarkers.Insert(new ref BasicMapMarker("Green Mountain", "BasicMap\\gui\\images\\marker.paa", Vector(3693.56, 402.312,6010.05), {111, 3, 252}));
		ServerMarkers.Insert(new ref BasicMapMarker("Kumyrna", "BasicMap\\gui\\images\\marker.paa", Vector(8345.61, 292.302, 5985.93),  {111, 3, 252}));
		JsonFileLoader< array<ref BasicMapMarker> >.JsonSaveFile(ServerMarkersPath, ServerMarkers);
	}

	
	ref BasicMapMarker Marker(int i){
		int ServerMarkersIndex = 0;
		int ServerMarkersCount = ServerMarkers.Count();
		int ClientMarkersIndex = ServerMarkers.Count();
		int ClientMarkersCount = ClientMarkersIndex + ClientMarkers.Count();
		int GroupMarkerIndex = ClientMarkersCount;
		int GroupMarkerCount = ClientMarkersCount + GroupMarkers.Count();
		if (i < ServerMarkers.Count()){
			return ServerMarkers.Get(i);
		} else if ( i < ClientMarkersCount){
			i = i - ClientMarkersIndex;
			return ClientMarkers.Get(i);
		} else if ( i < GroupMarkerCount){
			i = i - GroupMarkerIndex;
			return GroupMarkers.Get(i);
		}
		return NULL;
	}
	
	int Count(){
		return ServerMarkers.Count() + ClientMarkers.Count() + GroupMarkers.Count();
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