modded class AirdropBase
{
	//A place to remember the last known drop point
	protected vector m_BMLastDropPoint;
	
	
	void AirdropBase(){
		//Making sure its the server
		if (GetGame().IsServer()){
			GetAirdropBasicMapConfig();
			// Registering the RPC call for getting the last airdrop location
			GetRPCManager().AddRPC( "BasicMap", "RPCGetLastAirdrop", this, SingeplayerExecutionType.Both );
			Print("[BasicMap] [Airdrop] Server Init");
		}
	}
	
	//Rpc call for when a client request the last know location
	void RPCGetLastAirdrop( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ){
		//If sender is valid and the last airdrop location is set send the last known airdrop location
		if (sender && m_BMLastDropPoint){
			Print("[BasicMap] [Airdrop] Sending Last Airdrop Location");
			GetRPCManager().SendRPC("BasicMap", "RPCOnCallAirdrop", new Param3< vector, float, vector >( m_BMLastDropPoint, GetAirdropBasicMapConfig().CircleDrawRadius, GetAirdropBasicMapConfig().CircleColor), true, sender);
		}
	}
	
	//Called 
	override void EOnCallAirdrop(bool playercalled, vector droppoint)
	{
		super.EOnCallAirdrop(playercalled, droppoint);
		//Null pointer check and server check
		if ( /* !playercalled && */ m_DropPoint && GetGame().IsServer()){
			//^ Remove comments to prevent playercalled airdrops from being added to the map
			
			//Randomly generating new X and Y coordinates base on the droppoint
			//m_DropPoint is the actual drop point of the chest since airdrop randomize the actual drop point
			float rndT = Math.RandomFloat(0,1) * 2 * Math.PI;
			float rndR = GetAirdropBasicMapConfig().CircleRndRadius * Math.Sqrt(Math.RandomFloat(0,1)) * 0.85; //reducing by 15% to then add 15%
			//Adding 15% of the radius to make so its not in the center feel like this will just seem less random
			float rndRD = GetAirdropBasicMapConfig().CircleRndRadius * 0.15;
			rndR = rndR + rndRD;

			float NewX = m_DropPoint[0] + rndR * Math.Cos(rndT);
			float NewY = m_DropPoint[2] + rndR * Math.Sin(rndT);
			
			//Setting the last known to be this new location
			m_BMLastDropPoint = Vector(NewX, GetGame().SurfaceY(NewX,NewY), NewY);
			
			float Distance = vector.Distance(Vector(m_DropPoint[0],0,m_DropPoint[2]),Vector(m_BMLastDropPoint[0],0,m_BMLastDropPoint[2]));
			Print("[BasicMap] [Airdrop] Airdrop location: " + m_DropPoint + " Circle Center: " + m_BMLastDropPoint + " Distance: " + Distance + " rndR:" + rndR + " rndT: " + rndT);
			
			//Sending the center of the markers to all the clients
			GetRPCManager().SendRPC("BasicMap", "RPCOnCallAirdrop", new Param3< vector, float, vector >( m_BMLastDropPoint, GetAirdropBasicMapConfig().CircleDrawRadius, GetAirdropBasicMapConfig().CircleColor ), true, NULL);
		}
	}

}