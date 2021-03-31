#ifdef NAMALSK_SURVIVAL
modded class dzn_map_namalsk  extends ItemMap
{
	protected ref array<ref BasicMapMarker> 	m_BasicMapMarkerArray = new array<ref BasicMapMarker>;
	
	//Only used if using Basic Treasure Maps
	protected vector m_TreasureLocation;
	
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
		
		if (!ctx.Read(m_TreasureLocation))
		{
			return false;
		}
		
		
		return true;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		ctx.Write(m_BasicMapMarkerArray);
		
		ctx.Write(m_TreasureLocation);
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
					m_BasicMapMarkerArray = new array<ref BasicMapMarker>; //Weird issues doing if I just set the array
					for (i = 0; i < data.param1.Count(); i++){
						m_BasicMapMarkerArray.Insert(data.param1.Get(i));
					}
				}
			}
		}
	}
	
	#ifdef BASICTREASURES
		
	
	override void EEOnCECreate(){
		super.EEOnCECreate();
		
		float rand = Math.RandomFloat(0,1);
		if ( !GetGame().IsServer() || rand >  this.GenerateTreasureSpawnChance() || !BasicMap().CanSpawnNewChest()){
			return;
		}
		
		m_TreasureLocation = this.GenerateSpawnPos();
		if (IsTreasureAlreadySpawned()){
			return;
		}
		BasicMap().NewChestSpawned();

		Print("[Treasure] Map Spawned at: " + GetPosition() );

		UndergroundStash stash = UndergroundStash.Cast( GetGame().CreateObject( "UndergroundStash",  m_TreasureLocation));
		if (stash){
			stash.PlaceOnGround(); 
			stash.SetLifetime(430000);
			vector pos = stash.GetPosition();
			vector ori = stash.GetOrientation();
			m_TreasureLocation = pos;
			
			if ( ori[2] == -180 || ori[2] == 180 ){
				ori[2] = 0;
				stash.SetOrientation( ori );
			}
			BasicTreasuresRewardPool TheRewards = GetBasicTreasuresConfig().GetRandomRewardPool();
			ItemBase TheTreasure = ItemBase.Cast( stash.GetInventory().CreateInInventory("SeaChest"));	
			if (TheTreasure){
				for (int i = 0; i < TheRewards.Rewards.Count(); i++){
					EntityAI item = EntityAI.Cast(TheTreasure.GetInventory().CreateInInventory( TheRewards.Rewards.Get(i).Item));
					if (item){
						TStringArray attachments = TheRewards.Rewards.Get(i).ItemAttachments;
						if (attachments && attachments.Count() > 0){
							for (int j = 0;j < attachments.Count(); j++){
								item.GetInventory().CreateInInventory(attachments.Get(j));
							}
						}
					}
				}
			}
		
			ref BasicMapMarker theMarker = new BasicMapMarker("X", pos, "BasicTreasures\\gui\\images\\x.paa", {226, 144, 17}, 200, false);
			theMarker.SetCanEdit(false);
			m_BasicMapMarkerArray.Insert(theMarker);
		}
	}

	bool IsTreasureAlreadySpawned(){
		array<Object> objects = new array<Object>;
		array<CargoBase> proxyCargos = new array<CargoBase>;
		GetGame().GetObjectsAtPosition3D(m_TreasureLocation, 2, objects, proxyCargos);
		UndergroundStash stash;
		for (int i = 0; i < objects.Count(); i++){
			if ( Class.CastTo(stash, objects.Get(i)) ){
				return true;
			}
		}
		return false;
	}


	
	override void EEDelete(EntityAI parent){
		array<Object> objects = new array<Object>;
		array<CargoBase> proxyCargos = new array<CargoBase>;
		GetGame().GetObjectsAtPosition3D(m_TreasureLocation, 3, objects, proxyCargos);
		UndergroundStash stash;
		SeaChest chest;
		for (int i = 0; i < objects.Count(); i++){
			if ( Class.CastTo(stash, objects.Get(i)) ){
				Print("[Treasure] Map at " + GetPosition() +  "  Deleted Stash: " + m_TreasureLocation );
				GetGame().ObjectDelete(stash);
				super.EEDelete(parent);
				return;
			}
			if ( Class.CastTo(chest, objects.Get(i)) ){
				Print("[Treasure] Map at " + GetPosition() +  "  Deleted Chest: " + m_TreasureLocation );
				GetGame().ObjectDelete(chest);
			}
		}
		
		super.EEDelete(parent);
	}

	
	vector GenerateSpawnPos(){
		return BasicMap().GetRandomChestSpawn();
	}	
	
	
	float GenerateTreasureSpawnChance(){
		return GetBasicTreasuresConfig().ChanceOnSpawn;
	}
	
	
	#endif
	
}
#endif