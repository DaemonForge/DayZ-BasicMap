class BasicMapMarker {
	string Name = "";
	string Icon = "BasicMap\\gui\\images\\marker.paa";
	bool Is3DMarker = false;
	vector Pos = Vector(0,0,0);
	ref array<int> Colour = {0,0,0};
	int Alpha = 235;
	
	void BasicMapMarker(string name, string icon, vector pos, ref array<int> colour, int alpha = 235, bool onHUD = false){
		Name = name;
		Icon = icon;
		Pos = pos;
		Colour = colour;
		Alpha = alpha;
		OnHUD = onHUD;
	}
	
	void ShowOnHUD(bool onHUD = true){
		OnHUD = onHUD;
	}
	
	bool OnHUD(){
		return Is3DMarker;
	}
	
	string GetName(){
		return Name;
	}
	
	void SetPosition(vector pos){
		Pos = pos;
	}
	
	vector GetPosition(){
		return Pos;
	}
	
	int GetColour(){
		int a = Alpha;
		int r = Colour[0];
		int g  = Colour[1];
		int b  = Colour[2];
		return ARGB(a, r, g, b);
	}
	
	int GetColor(){ // :P
		return GetColour();
	}
	
}

class BasicMapPlayerMarker extends BasicMapMarker{
	ref DayZPlayer m_player;
	
	override string GetName(){
		if (m_player.GetIdentity()){
			return m_player.GetIdentity().GetName();
		}
		return "";
	}
	
	override vector GetPosition(){
		return m_player.GetPosition();
	}

}