modded class AirdropBase
{	
	
	void AirdropBase(){
		//Making sure its the server
		if (GetGame().IsServer()){
			GetAirdropBasicMapConfig();
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
			vector m_BMLastDropPoint = Vector(NewX, GetGame().SurfaceY(NewX,NewY), NewY);
			
			float Distance = vector.Distance(Vector(m_DropPoint[0],0,m_DropPoint[2]),Vector(m_BMLastDropPoint[0],0,m_BMLastDropPoint[2]));
			Print("[BasicMap] [Airdrop] Airdrop location: " + m_DropPoint + " Circle Center: " + m_BMLastDropPoint + " Distance: " + Distance + " rndR:" + rndR + " rndT: " + rndT);
			 
			//Cause Enfusion Sucks
			float red = GetAirdropBasicMapConfig().CircleColor[0];
			float green = GetAirdropBasicMapConfig().CircleColor[1];
			float blue = GetAirdropBasicMapConfig().CircleColor[2]; 
			int ired = red;
			int igreen = green;
			int iblue = blue;
			
			
			
			//Create Marker
			BasicMapCircleMarker marker = new BasicMapCircleMarker( "", m_BMLastDropPoint, AIRDROP_ICON_AIRDROP, {ired,igreen,iblue}, 248, false);
			
			//Prevent Editing of the marker
			marker.SetCanEdit(false);
			//Making it so the icon shows in the center
			marker.SetShowCenterMarker(true);
			//Setting hide Intersects to true this way if you have other circle markers this will show in full
			marker.SetHideIntersects(false);
			//Set Radius
			marker.SetRadius(GetAirdropBasicMapConfig().CircleDrawRadius);
			
			
			//Add Marker
			array<ref BasicMapMarker> markers = new array<ref BasicMapMarker>;
			markers.Insert(marker);
			
			//Set the Marker
			BasicMap().SetMarkers("AirDrops", markers);
			
			//Update all the clients
			BasicMap().UpdateGroupRemote("AirDrops");
		}
	}

}