class BasicMapPlayerMarker extends BasicMapMarker {
	
	protected DayZPlayer m_player;
	void BasicMapPlayerMarker(string name, vector pos, string icon = "", array<int> colour = NULL, int alpha = 235, bool onHUD = false){
		Name = name;
		Pos = pos;
		if (icon != ""){
			Icon = icon;
		} else {
			Icon = "BasicMap\\gui\\images\\player.paa";
		}
		Pos = pos;
		if (colour != NULL){
			Colour = colour;
		} else {
			Colour = {33, 233, 255};
		}
		Alpha = alpha;
		Is3DMarker = onHUD;
	}
	
	void SetPlayer(DayZPlayer player){
		m_player = DayZPlayer.Cast(player);
	}
	
	override string GetName(){
		DayZPlayer player = DayZPlayer.Cast(m_player);
		if (player && player.GetIdentity()){
			return player.GetIdentity().GetName();
		}
		return Name;
	}
	
	override vector GetPosition(){
		DayZPlayer player = DayZPlayer.Cast(m_player);
		if (player && player.GetIdentity()){
			return player.GetPosition();
		}
		return Pos;
	}

	
}