class BasicMapCircleMarker extends BasicMapMarker{
	
	bool ShowCenterMarker = false;
	
	float Radius = 0;
	
	bool HideIntersects = true;
		
	[NonSerialized()]
	ref array<vector> Edge;
	
	[NonSerialized()]
	bool Updated = true;
	
	
	void SetUpdated(bool state){
		Updated = state;
	}
	
	bool GetUpdated(){
		return Updated;
	}
	
	override void SetPosition(vector pos){
		super.SetPosition(pos);
		Updated = true;
	}
	
	override void SetIcon(string icon){
		super.SetIcon(icon);
		Updated = true;
	}
	
	override void SetARGB(int A, int R, int G, int B){
		super.SetARGB(A, R, G, B);
		Updated = true;
	}
	
	void SetShowCenterMarker(bool state){
		ShowCenterMarker = state;
	}
	
	bool GetShowCenterMarker(){
		return ShowCenterMarker;
	}
	
	void SetRadius(float radius){
		Radius = radius;
		Updated = true;
	}
	
	float GetRadius(){
		return Radius;
	}
	
	void SetHideIntersects(float state){
		HideIntersects = state;
		Updated = true;
	}
	
	bool GetHideIntersects(){
		return HideIntersects;
	}
	
	array<vector> GetEdge(array<ref BasicMapMarker> Conflicting = NULL) {
		if ( !GetUpdated() && Edge && Edge.Count() > 0){
			return Edge;
		}
		Updated = false;
		Edge = new array<vector>;
		float circleLength = Math.PI * GetRadius();
		circleLength = circleLength * 0.65;
		int i = 0;
		float slice = 2 * Math.PI / circleLength;
		while (i <= circleLength) {
			float angle = slice * i;
			float x = Pos[0] + GetRadius() * Math.Cos(angle);
			float y = Pos[2] + GetRadius() * Math.Sin(angle);
			if (!GetHideIntersects() || !Intersects(Vector(x, Pos[1], y), Conflicting)){
				if ( x >= 0 && y >= 0 && x <= 15360 && y <= 15360){//Prevent markers out of bounds
					Edge.Insert(Vector(x, Pos[1], y));
				}
			}
			i++;
		}
		return Edge;
	}
	
	
	bool Intersects(vector posToCheck, array<ref BasicMapMarker> Conflicting) {
		if (Conflicting){
			for (int i = 0; i < Conflicting.Count(); i++) {
				BasicMapCircleMarker MarkToCheck = BasicMapCircleMarker.Cast(Conflicting.Get(i));
				if (MarkToCheck && MarkToCheck.GetHideIntersects() && MarkToCheck.GetRadius() > 0 && MarkToCheck.GetPosition() != this.GetPosition()){ //Make sure to not check against self
					if (vector.Distance(MarkToCheck.GetPosition(), posToCheck) <= MarkToCheck.GetRadius()) {
						return true;
					}
				}
			}
		}
		return false;
	}
	
	
	string GetEdgeIcon(float scale = 1){
		if (scale < 0.013){
			return "BasicMap\\gui\\images\\dot3.paa";
		}
		if (scale < 0.072){
			return "BasicMap\\gui\\images\\dot2.paa";
		}
		return "BasicMap\\gui\\images\\dot.paa";
	}
	
	int GetEdgeColour(){
		return GetColour();
	}
	
	
	override string GetType(){
		return "CircleMarker";
	}
	
	override void PrintDebug(){
		Print(" = = = = = = = = = = = = = = = = = = ");
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
		Print("Radius: " + Radius);
		Print("HideIntersects: " + HideIntersects);
		Print("ShowCenterMarker: " + ShowCenterMarker);
		Print("EdgeIcon: " + GetEdgeIcon());
		Print("EdgeColour: " + GetColour());
		Print(" = = = = = = = = = = = = = = = = = = ");
		Print(" ");
	}
}