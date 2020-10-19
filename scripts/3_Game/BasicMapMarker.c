class BasicMapMarker {
	string Name = "";
	string Icon = "BasicMap\\gui\\images\\marker.paa";
	bool OnHUD = false;
	vector Pos = Vector(0,0,0);
	vector Colour = Vector(0,0,0);
	float Alpha = 0.9;
	
	void BasicMapMarker(string name, string icon, vector pos, vector colour, float alpha = 0.9, bool onHUD = false){
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
		return VectortoRGBA(Colour, Alpha);
	}
	
	int GetColor(){ // :P
		return GetColour();
	}
	
}