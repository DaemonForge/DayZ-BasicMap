class BasicMapMarker {
	string Name = "";
	string Icon = "BasicMap\\gui\\images\\marker.paa";
	bool OnHUD = false;
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