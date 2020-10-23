class BasicMapMarker {
	string Name = "";
	vector Pos = Vector(0,0,0);
	string Icon = "BasicMap\\gui\\images\\marker.paa";
	bool Is3DMarker = false;
	ref array<int> Colour = {119, 136, 198};
	int Alpha = 235;
	
	[NonSerialized()]
	protected bool CanEdit = false;
	
	[NonSerialized()]
	protected string Group = "";
	
	void BasicMapMarker(string name, vector pos, string icon = "", array<int> colour = NULL, int alpha = 235, bool onHUD = false) {
		Name = name;
		if (icon != ""){
			Icon = icon;
		}
		Pos = pos;
		if (colour != NULL){
			Colour = colour;
		}
		Alpha = alpha;
		Is3DMarker = onHUD;
	}
	
	
	void ShowOnHUD(bool onHUD = true){
		Is3DMarker = onHUD;
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
	
	
	string GetIcon(){
		return Icon;
	}
	
	
	void SetIcon(string icon){
		Icon = icon;
	}
	
	
	void SetCanEdit(bool canEdit){
		CanEdit = canEdit;
	}
	
	
	bool Editable(){
		return CanEdit;
	}
	
	void SetGroup(string group){
		Group = group;
	}
	
	string GetGroup(){
		return Group;
	}
	
	void SetVar(string vars, ParamsReadContext ctx){
  
	}
}

class BasicMapPlayerMarker extends BasicMapMarker {
	
	DayZPlayer m_player;
	
	void BasicMapPlayerMarker(string name, vector pos, string icon = "", array<int> colour = NULL, int alpha = 235, bool onHUD = false) {
		Name = name;
		if (icon != ""){
			Icon = icon;
		} else {
			Icon = "BasicMap\\gui\\images\\me.paa";
		}
		Pos = pos;
		if (colour != NULL){
			Colour = colour;
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
	
	override string GetIcon(){
		return "BasicMap\\gui\\images\\me.paa";
	}
	
}