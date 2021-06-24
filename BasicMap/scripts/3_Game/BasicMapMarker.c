class BasicMapMarker extends Managed{
	string Name = "";
	vector Pos = Vector(0,0,0);
	string Icon = "BasicMap\\gui\\images\\marker.paa";
	bool Is3DMarker = false;
	ref array<int> Colour = {119, 136, 198};
	int Alpha = 235;
	
	bool HideOnPanel = false;
	
	bool HideOnMap = false;
	
	float MaxRenderDistance = -1;
	float MinRenderDistance = -1;
	
	protected string MapToShowOn = "";
	protected bool CanEdit = true;
	protected string Group = BasicMap().CLIENT_KEY;
	
	
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
		GetGame().GetWorldName(MapToShowOn);
		MapToShowOn.ToLower();
	}	
	
	
	void ShowOnHUD(bool onHUD = true){
		Is3DMarker = onHUD;
	}
	
	void UpdateMap(string mapname = ""){
		if (mapname != ""){
			mapname.ToLower();
			MapToShowOn = mapname;
			return;
		}
		GetGame().GetWorldName(MapToShowOn);
		MapToShowOn.ToLower();
	}
	
	string GetMapToShowOn(){
		return MapToShowOn;
	}
	
	bool IsCorrectMap(){
		if (!GetMapToShowOn() || GetMapToShowOn() == "" || GetMapToShowOn() == "any" || GetMapToShowOn() == "all"){
			return true;
		}
		string CurrentMap = "";
		GetGame().GetWorldName(CurrentMap);
		CurrentMap.ToLower();
		return (CurrentMap == GetMapToShowOn());
	}
	
	bool OnHUD(){
		if (!IsCorrectMap()) {
			return false;
		}
		if (!MinRenderDistance){
			MinRenderDistance = -1;
		}
		if (!MaxRenderDistance){
			MaxRenderDistance = -1;
		}
		DayZPlayer thePlayer = DayZPlayer.Cast(GetGame().GetPlayer());
		if ( MinRenderDistance != -1 && thePlayer){
			if (vector.Distance( thePlayer.GetPosition(), GetPosition()) <= MinRenderDistance){
				return false;
			}
		} else if ( MaxRenderDistance != -1 && thePlayer){
			if (vector.Distance( thePlayer.GetPosition(), GetPosition()) >= MaxRenderDistance){
				return false;
			}
		} 
		return Is3DMarker;
	}
	
	void SetName(string name){
		Name = name;
	}
	
	string GetName(){
		return Name;
	}
	
	
	void SetPosition(vector pos){
		Pos = pos;
	}
	
	
	vector GetPosition(){
		if (!Pos){
			return Vector(0,0,0,);
		}
		return Pos;
	}
	
	void SetARGB(int A, int R, int G, int B){
		Alpha = A;
		Colour = {R, G, B};
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
		if (!Group){
			return "";
		}
		return Group;
	}
	
	void SetVar(string vars, ParamsReadContext ctx){
  
	}
	
	void SetHideOnPanel(float state){
		HideOnPanel = state;
	}
	
	bool OnPanel(){
		if (!IsCorrectMap()) {
			return false;
		}
		return !HideOnPanel;
	}
	
	void SetHideOnMap(bool state){
		HideOnMap = state;
	}
	
	bool OnMap(){
		if (!IsCorrectMap()) {
			return false;
		}
		if (!MinRenderDistance){
			MinRenderDistance = -1;
		}
		if (!MaxRenderDistance){
			MaxRenderDistance = -1;
		}
		
		DayZPlayer thePlayer = DayZPlayer.Cast(GetGame().GetPlayer());
		if (MinRenderDistance != -1 && thePlayer){
			if (vector.Distance( thePlayer.GetPosition(), GetPosition()) <= MinRenderDistance){
				return false;
			}
		} else if (MaxRenderDistance != -1 && thePlayer){
			if (vector.Distance( thePlayer.GetPosition(), GetPosition()) >= MaxRenderDistance){
				return false;
			}
		}
		return !HideOnMap;
	}
	
	bool ShowDistance(){
		return true;
	}
	
	void PrintDebug(){
		Print(" = = = = = = = = = = = = = = ");
		Print("Name: " + Name);
		Print("Pos: " + Pos);
		Print("Icon: " + Icon);
		Print("Is3DMarker: " + Is3DMarker);
		Print("Colour: ");
		Colour.Debug();
		Print("Alpha: " + Alpha);
		Print("CanEdit: " + CanEdit);
		Print("Group: " + Group);
		Print("Type: " + GetType());
		Print(" = = = = = = = = = = = = = = ");
		Print(" ");
	}
	
	string GetType(){
		return "BasicMarker";
	}
}