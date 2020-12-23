#ifdef NAMALSK_SURVIVAL
modded class dzn_map_namalsk  extends ItemMap
{
	protected ref array<ref BasicMapMarker> 	m_BasicMapMarkerArray = new ref array<ref BasicMapMarker>;
	
	override void SetActions()
	{
		super.SetActions();
		RemoveAction(ActionUnfoldMap);
		AddAction(ActionOpenBasicMap);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
	
		if (!ctx.Read(m_BasicMapMarkerArray))
		{
			return false;
		}
		return true;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		ctx.Write(m_BasicMapMarkerArray);
	}
	
	ref array<ref BasicMapMarker> GetBasicMapMarkers()
	{
		return m_BasicMapMarkerArray;
		
	}
	
	override void SyncMapMarkers()
	{
		super.SyncMapMarkers();
		if (GetGame().IsServer() && GetHierarchyRootPlayer()) {
			PlayerIdentity  pid = PlayerIdentity.Cast(GetHierarchyRootPlayer().GetIdentity());
			if (pid) {
				RPCSingleParam(BASICMAPRPCs.SEND_MARKERS, new Param1<ref array<ref BasicMapMarker>>( m_BasicMapMarkerArray ), true, pid);
			}
		} else if (GetGame().IsClient() && GetHierarchyRootPlayer()){
			RPCSingleParam(BASICMAPRPCs.REQUEST_MARKERS, new Param1<bool>( true ), true, NULL);
		}
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		int i;
		Param1<array<ref BasicMapMarker>> data;
		array<ref BasicMapMarker> Markers;
		PlayerIdentity  pid = PlayerIdentity.Cast(GetHierarchyRootPlayer().GetIdentity());
		
		if (rpc_type == BASICMAPRPCs.SEND_MARKERS && GetGame().IsClient()) {
			if (ctx.Read(data))	{
				Markers = array<ref BasicMapMarker>.Cast(data.param1);
				if (Markers){
					m_BasicMapMarkerArray = new array<ref BasicMapMarker>; //Weird issues doing if I just set the array
					for (i = 0; i < data.param1.Count(); i++){
						m_BasicMapMarkerArray.Insert(data.param1.Get(i));
					}
					if (GetGame().IsClient() && GetHierarchyRootPlayer() == GetGame().GetPlayer()){
						BasicMap().SetMarkers(BasicMap().CLIENT_KEY, m_BasicMapMarkerArray);
					}
				}
			}
		}
		if (rpc_type == BASICMAPRPCs.REQUEST_MARKERS && GetGame().IsServer()) {
			if (GetHierarchyRootPlayer() && sender.GetId() == GetHierarchyRootPlayer().GetIdentity().GetId()){
				this.SyncMapMarkers();
			}
		}
		if (rpc_type == BASICMAPRPCs.SAVE_MARKERS && GetGame().IsServer()){
			if (ctx.Read(data)){
				Markers = array<ref BasicMapMarker>.Cast(data.param1);
				if (Markers){
					m_BasicMapMarkerArray = new ref array<ref BasicMapMarker>; //Weird issues doing if I just set the array
					for (i = 0; i < data.param1.Count(); i++){
						m_BasicMapMarkerArray.Insert(data.param1.Get(i));
					}
				}
			}
		}
	}
}
#endif