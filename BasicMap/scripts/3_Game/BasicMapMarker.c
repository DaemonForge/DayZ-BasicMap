class BasicMapMarker extends Managed{
	string Name = "";
	vector Pos = Vector(0,0,0);
	string Icon = "BasicMap\\gui\\images\\marker.paa";
	bool Is3DMarker = false;
	autoptr array<int> Colour = {119, 136, 198};
	int Alpha = 235;
	 
	bool HideOnPanel = false;
	
	bool HideOnMap = false;
	
	float MaxRenderDistance = -1;
	float MinRenderDistance = -1;
	
	protected string MapToShowOn = "";
	protected bool CanEdit = true;
	protected string Group = BasicMap().CLIENT_KEY;
	
	// Cached current world name (same for all markers, never changes at runtime)
	protected static string s_CachedCurrentMap = "";
	protected static bool s_CurrentMapCached = false;
	
	
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
	
	// Get the cached current map name (avoids repeated GetWorldName calls)
	protected static string GetCurrentMapCached(){
		if (!s_CurrentMapCached){
			GetGame().GetWorldName(s_CachedCurrentMap);
			s_CachedCurrentMap.ToLower();
			s_CurrentMapCached = true;
		}
		return s_CachedCurrentMap;
	}
	
	bool IsCorrectMap(){
		string showOn = GetMapToShowOn();
		if (!showOn || showOn == "" || showOn == "any" || showOn == "all"){
			return true;
		}
		return (GetCurrentMapCached() == showOn);
	}
	
	// Shared render-distance check used by OnHUD() and OnMap()
	// Returns false if the marker is outside its configured render range
	protected bool IsWithinRenderDistance(){
		if (!MinRenderDistance){
			MinRenderDistance = -1;
		}
		if (!MaxRenderDistance){
			MaxRenderDistance = -1;
		}
		if (MinRenderDistance == -1 && MaxRenderDistance == -1){
			return true;
		}
		DayZPlayer thePlayer = DayZPlayer.Cast(GetGame().GetPlayer());
		if (!thePlayer){
			return true;
		}
		float dist = vector.Distance(thePlayer.GetPosition(), GetPosition());
		if (MinRenderDistance != -1 && dist <= MinRenderDistance){
			return false;
		}
		if (MaxRenderDistance != -1 && dist >= MaxRenderDistance){
			return false;
		}
		return true;
	}
	
	bool OnHUD(){
		if (!IsCorrectMap()) {
			return false;
		}
		if (!IsWithinRenderDistance()){
			return false;
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
			return Vector(0,0,0);
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
	
	void SetHideOnPanel(bool state){
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
		if (!IsWithinRenderDistance()){
			return false;
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