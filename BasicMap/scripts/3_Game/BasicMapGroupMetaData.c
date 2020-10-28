class BasicMapGroupMetaData {
	
	string ID;
	
	string Name;
	
	bool CanCreate = false;
	
	bool ShowOnHUD = true;
	bool ShowOnMap = true;
	
	
	void BasicMapGroupMetaData(string id, string name, bool canCreate = false){
		ID = id;
		Name = name;
		CanCreate = canCreate;
	}
	
	string GetDisplayName(){
		return Name;
	}
	
	bool Creatable(){
		return CanCreate;
	}
	
	void SetOnHUD(bool onHUD){
		ShowOnHUD = onHUD;
	}
	
	bool OnHUD(){
		return ShowOnHUD;
	}
	
	void SetOnMap(bool onMap){
		ShowOnMap = onMap;
	}
	
	bool OnMap(){
		return ShowOnMap;
	}
}