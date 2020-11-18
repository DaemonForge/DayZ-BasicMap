class BasicMapCircleMarker extends BasicMapMarker{
	
	bool ShowCenterMarker = false;
	
	float Radius = 0;
	
	bool HideIntersects = true;
	
	
	
	void SetShowCenterMarker(bool state){
		ShowCenterMarker = state;
	}
	
	bool GetShowCenterMarker(){
		return ShowCenterMarker;
	}
	
	void SetRadius(float radius){
		Radius = radius;
	}
	
	float GetRadius(){
		return Radius;
	}
	
	void SetHideIntersects(float state){
		HideIntersects = state;
	}
	
	bool GetHideIntersects(){
		return HideIntersects;
	}
	
	array<vector> GetEdge(array<ref BasicMapMarker> Conflicting = NULL) {
		array<vector> edge = new array<vector>;
		float circleLength = Math.PI * GetRadius();
		int i = 0;
		float slice = 2 * Math.PI / circleLength;
		while (i < circleLength) {
			float angle = slice * i;
			float x = Pos[0] + GetRadius() * Math.Cos(angle);
			float y = Pos[2] + GetRadius() * Math.Sin(angle);
			if (!GetHideIntersects() || !Intersects(Vector(x, Pos[1], y), Conflicting)){
				edge.Insert(Vector(x, Pos[1], y));
			}
			i++;
		}
		return edge;
	}
	
	
	bool Intersects(vector posToCheck, array<ref BasicMapMarker> Conflicting) {
		if (Conflicting){
			for (int i = 0; i < Conflicting.Count(); i++) {
				BasicMapCircleMarker MarkToCheck = BasicMapCircleMarker.Cast(Conflicting.Get(i));
				if (MarkToCheck && MarkToCheck.GetRadius() > 0 && MarkToCheck.GetPosition() != this.GetPosition()){ //Make sure to not check against self
					if (vector.Distance(MarkToCheck.GetPosition(), posToCheck) <= MarkToCheck.GetRadius()) {
						return true;
					}
				}
			}
		}
		return false;
	}
	
	
	string GetEdgeIcon(){
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