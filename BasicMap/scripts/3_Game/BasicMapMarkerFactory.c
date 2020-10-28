class BasicMapMarkerFactory {
	
    ref BasicMapMarker Create(string name, vector position) {
		BasicMapMarker marker = new ref BasicMapMarker(name, position);
		marker.SetIcon("BasicMap\\gui\\images\\marker.paa");
		marker.SetGroup(BasicMap().CLIENT_KEY);
		marker.ShowOnHUD(true);
		marker.Colour.Set(0,119);
		marker.Colour.Set(1,136);
		marker.Colour.Set(2,198);
		marker.Alpha = 235;
		marker.SetCanEdit(true);
        return marker;
    }
	
}