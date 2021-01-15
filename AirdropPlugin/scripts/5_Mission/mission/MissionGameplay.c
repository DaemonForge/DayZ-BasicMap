modded class MissionGameplay extends MissionBase
{
	//Reference Markers so we can edit it without having to grab it from basic map over and over again
	ref BasicMapCircleMarker m_AirDropMarker;   
	
	//This is called when the client starts playing
	override void OnMissionStart(){
		super.OnMissionStart();
		
		//Adding the reference for the RPC call so it knows which function to call when rpc comes from the server
		GetRPCManager().AddRPC( "BasicMap", "RPCOnCallAirdrop", this, SingeplayerExecutionType.Both );
		
		Print("[BasicMap] [Airdrop] Init - Requesting Last AirDrop Locations");
		//Sends an RPC request to the server asking for the last known airdrop location when the player connects 
		//This is so players who join after the drop know where to go
		GetRPCManager().SendRPC("BasicMap", "RPCGetLastAirdrop", new Param3< vector, float, vector >( vector.Zero, 0, vector.Zero ), true, NULL);
	}
	
	void RPCOnCallAirdrop( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ){
		//Reading the RPC calls data
		Param3< vector, float, vector > data; 
		if ( !ctx.Read( data ) ) return;
		
		vector AirdropRandomCenter = data.param1; //Getting the varible from the RPC call
		float AirdropRadius = data.param2;
		vector AirdropColour = data.param3;
		//If the Airdrop marker reference hasn't been created yet create it
		if (!m_AirDropMarker){
			Print("[BasicMap] [Airdrop] Creating First Marker ");

			//Have to cause enfusion sucks balls
			float red = AirdropColour[0];
			float green = AirdropColour[1];
			float blue = AirdropColour[2]; 
			int ired = red;
			int igreen = green;
			int iblue = blue;
			
			//Creating the first marker with the name,
			m_AirDropMarker = new ref BasicMapCircleMarker( "", AirdropRandomCenter, AIRDROP_ICON_AIRDROP, {ired,igreen,iblue}, 248, true);
			//Prevent Marker editing
			m_AirDropMarker.SetCanEdit(false);
			//Making it so the icon shows in the center
			m_AirDropMarker.SetShowCenterMarker(true);
			//Setting hide Intersects to true this way if you have other circle markers this will show in full
			m_AirDropMarker.SetHideIntersects(false);
			//Adding the marker to the controller under the server markers tab
			BasicMap().AddMarker("EVENT", m_AirDropMarker);
		}
		//Quick debug print
		Print("[BasicMap] [Airdrop] Updating Marker " + AirdropRandomCenter);
		
		//Setting Marker radius
		m_AirDropMarker.SetRadius(AirdropRadius);
		
		//Setting the new Position when the marker update comes in
		m_AirDropMarker.SetPosition(AirdropRandomCenter);
	}
	
}