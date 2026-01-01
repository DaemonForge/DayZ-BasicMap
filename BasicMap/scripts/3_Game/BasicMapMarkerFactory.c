class BasicMapMarkerFactory {
	
	// Remember the last used color for new markers (client-side memory)
	static int s_LastColorR = 119;
	static int s_LastColorG = 136;
	static int s_LastColorB = 198;
	static int s_LastAlpha = 235;
	static string s_LastIcon = "BasicMap\\gui\\images\\marker.paa";
	
	// Call this when a marker is edited to remember its color for next creation
	static void RememberColor(int r, int g, int b, int alpha, string icon = ""){
		s_LastColorR = r;
		s_LastColorG = g;
		s_LastColorB = b;
		s_LastAlpha = alpha;
		if (icon != ""){
			s_LastIcon = icon;
		}
	}
	
    BasicMapMarker Create(string name, vector position) {
		BasicMapMarker marker = new BasicMapMarker(name, position);
		marker.SetIcon(s_LastIcon);
		marker.SetGroup(BasicMap().CLIENT_KEY);
		marker.ShowOnHUD(true);
		marker.Colour.Set(0, s_LastColorR);
		marker.Colour.Set(1, s_LastColorG);
		marker.Colour.Set(2, s_LastColorB);
		marker.Alpha = s_LastAlpha;
		marker.SetCanEdit(true);
        return marker;
    }
	
}