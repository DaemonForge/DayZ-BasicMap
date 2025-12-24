class BasicMapHUDMarker extends Managed {
	
	protected bool						m_deleted = false;
	
	protected int 						m_logSkip = 100;
	protected string 					LayoutPath = "BasicMap/gui/layouts/Marker.layout";
	
	protected BasicMapMarker 			m_MarkerData;
	
	protected Widget 					layoutRoot;
	
	protected Widget					m_Marker;

	protected ImageWidget				m_Icon;
	protected TextWidget				m_Name;
	protected TextWidget				m_Distance;
	
	protected string					m_LastLoadedIcon = "";
	
	// Proximity fade settings - text shows when looking near marker
	protected float						m_ProximityRadius = 0.28; // 28% of screen from center (name starts fading)
	protected float						m_DistanceProximityRadius = 0.20; // 20% - distance fades in closer
	protected float						m_CurrentTextAlpha = 0;
	protected float						m_CurrentDistanceAlpha = 0;
	protected float						m_CurrentIconAlpha = 0.8; // Icon starts at 80%
	
	// Edge fade settings - fade out as marker approaches screen edges
	protected float						m_EdgeFadeSides = 0.15;   // 15% from sides
	protected float						m_EdgeFadeTopBottom = 0.08; // 8% from top/bottom
	
	void Init(BasicMapMarker markerData){
		m_MarkerData 	= BasicMapMarker.Cast(markerData);
		
		layoutRoot	 	= Widget.Cast(GetGame().GetWorkspace().CreateWidgets(LayoutPath));
		
		m_Marker 		= Widget.Cast( layoutRoot.FindAnyWidget( "Marker" ) );

		m_Icon			= ImageWidget.Cast( layoutRoot.FindAnyWidget( "Icon" ) );
		m_Name			= TextWidget.Cast( layoutRoot.FindAnyWidget( "Name" ) );
		m_Distance		= TextWidget.Cast( layoutRoot.FindAnyWidget( "Distance" ) );
		if (!m_MarkerData){
			return;
		}
		
		m_Name.SetText(m_MarkerData.GetName());
		if (m_MarkerData.GetIcon() != ""){
			m_LastLoadedIcon = m_MarkerData.GetIcon();
			m_Icon.LoadImageFile(0, m_MarkerData.GetIcon());
		} else {
			m_Marker.Show(false);
		}
		m_Icon.SetColor(m_MarkerData.GetColour());
		m_Name.SetColor(m_MarkerData.GetColour());
		m_Distance.SetColor(ARGB(230, 90, 145, 230)); // Subtle blue for distance
		
		// Start with text hidden
		if (m_Name) m_Name.SetAlpha(0);
		if (m_Distance) m_Distance.SetAlpha(0);
		
		Update();
		if (layoutRoot && m_Marker && m_MarkerData){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.Update, 14, true);
		}
	}
	
	void ~BasicMapHUDMarker(){
		OnDelete();
		delete layoutRoot;
	}
	
	void Update(){
		// Null safety checks
		if (!layoutRoot || m_deleted){
			OnDelete();
			return;
		}
		
		if (!m_MarkerData){
			Show(false);
			return;
		}
		
		// Ensure BasicMap controller exists
		if (!BasicMap()){
			Show(false);
			return;
		}
		
		if (MarkerVisibleOnScreen() && m_MarkerData.OnHUD() && BasicMap().ShowMarkersOnHUD() && BasicMap().ShouldShowOnHUD(m_MarkerData.GetGroup())){
				
				float x;
				float y;
				vector screenPosition = GetGame().GetScreenPos(m_MarkerData.GetPosition());
				x = Math.Round(screenPosition[0]);
		        y = Math.Round(screenPosition[1]);
				
				// Get screen dimensions
				int screenW, screenH;
				GetScreenSize(screenW, screenH);
				float centerX = screenW * 0.5;
				float centerY = screenH * 0.5;
				
				// Calculate proximity to screen center for text fade
				float distFromCenter = Math.Sqrt(Math.Pow(x - centerX, 2) + Math.Pow(y - centerY, 2));
				float maxDistName = screenH * m_ProximityRadius;
				float maxDistDistance = screenH * m_DistanceProximityRadius;
				
				// Calculate name alpha: 1.0 when at center, 0.0 when outside radius
				float targetTextAlpha = 0;
				if (distFromCenter < maxDistName){
					targetTextAlpha = 1.0 - (distFromCenter / maxDistName);
					targetTextAlpha = Math.Clamp(targetTextAlpha, 0, 1);
				}
				
				// Calculate distance alpha: fades in 20% closer than name
				float targetDistanceAlpha = 0;
				if (distFromCenter < maxDistDistance){
					targetDistanceAlpha = 1.0 - (distFromCenter / maxDistDistance);
					targetDistanceAlpha = Math.Clamp(targetDistanceAlpha, 0, 1);
				}
				
				// Get the marker's configured alpha (0-255) as the max
				int markerColor = m_MarkerData.GetColour();
				int configuredAlpha = (markerColor >> 24) & 0xFF;
				float maxAlphaPercent = configuredAlpha / 255.0; // Convert to 0-1 range
				
				// Calculate icon alpha: 100% of configured when text visible, 80% of configured when not
				float targetIconAlpha = (0.8 + (targetTextAlpha * 0.2)) * maxAlphaPercent;
				
				// Calculate edge fade - fade from 80% to 0% at screen edges
				float edgeFade = 1.0;
				float screenXNorm = x / screenW; // 0 to 1
				float screenYNorm = y / screenH; // 0 to 1
				
				// Left edge fade (10% from left)
				if (screenXNorm < m_EdgeFadeSides){
					edgeFade = Math.Min(edgeFade, screenXNorm / m_EdgeFadeSides);
				}
				// Right edge fade (10% from right)
				if (screenXNorm > (1.0 - m_EdgeFadeSides)){
					edgeFade = Math.Min(edgeFade, (1.0 - screenXNorm) / m_EdgeFadeSides);
				}
				// Top edge fade (5% from top)
				if (screenYNorm < m_EdgeFadeTopBottom){
					edgeFade = Math.Min(edgeFade, screenYNorm / m_EdgeFadeTopBottom);
				}
				// Bottom edge fade (5% from bottom)
				if (screenYNorm > (1.0 - m_EdgeFadeTopBottom)){
					edgeFade = Math.Min(edgeFade, (1.0 - screenYNorm) / m_EdgeFadeTopBottom);
				}
				
				// Apply edge fade to icon alpha (only affects the base 80%)
				targetIconAlpha = targetIconAlpha * edgeFade;
				
				// Smooth fade transitions (faster lerp for smoother zoom behavior)
				m_CurrentTextAlpha = Math.Lerp(m_CurrentTextAlpha, targetTextAlpha, 0.25);
				m_CurrentDistanceAlpha = Math.Lerp(m_CurrentDistanceAlpha, targetDistanceAlpha, 0.25);
				m_CurrentIconAlpha = Math.Lerp(m_CurrentIconAlpha, targetIconAlpha, 0.25);
				
				// Apply alpha to icon (uses color components from markerColor already extracted)
				if (m_Icon){
					int ir = (markerColor >> 16) & 0xFF;
					int ig = (markerColor >> 8) & 0xFF;
					int ib = markerColor & 0xFF;
					int iconAlphaInt = Math.Round(m_CurrentIconAlpha * 255);
					m_Icon.SetColor(ARGB(iconAlphaInt, ir, ig, ib));
				}
				
				// Apply alpha to text widgets (relative to configured max alpha)
				if (m_Name){
					if (m_CurrentTextAlpha > 0.02){
						m_Name.Show(true);
						
						int r = (markerColor >> 16) & 0xFF;
						int g = (markerColor >> 8) & 0xFF;
						int b = markerColor & 0xFF;
						// Text alpha is relative to configured max
						int newAlpha = Math.Round(m_CurrentTextAlpha * edgeFade * configuredAlpha);
						m_Name.SetColor(ARGB(newAlpha, r, g, b));
					} else {
						m_Name.Show(false);
					}
				}
				
				// Apply alpha to distance (fades in closer than name)
				if (m_Distance){
					if (m_CurrentDistanceAlpha > 0.02){
						m_Distance.Show(true);
						int distAlpha = Math.Round(m_CurrentDistanceAlpha * edgeFade * 255);
						m_Distance.SetColor(ARGB(distAlpha, 90, 145, 230));
					} else {
						m_Distance.Show(false);
					}
				}
				
				if (m_MarkerData.ShowDistance()){
					float distance = 0;
					
					DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());
					if (player){
						distance =  Math.Round(vector.Distance(player.GetPosition(), m_MarkerData.GetPosition()));
					}
					string distanceText = distance.ToString() + "m";
					if (distance > 1000){
						distance = distance / 100;
						distance = Math.Round(distance);
						distance = distance / 10;
						distanceText = distance.ToString() + "km";
					}
					if (distance > 0){
						m_Distance.SetText(distanceText);
					} else {
						m_Distance.SetText("");
					}
				}
				
				if (m_LastLoadedIcon != m_MarkerData.GetIcon()){
					m_LastLoadedIcon = m_MarkerData.GetIcon();
					if (m_MarkerData.GetIcon() != ""){
						m_Icon.LoadImageFile(0, m_MarkerData.GetIcon());
						m_Marker.Show(true);
					} else {
						m_Marker.Show(false);
					}
				}
				Show();
				layoutRoot.SetPos(x, y);
		} else{
			Show(false);
		}
	}
	
	void Show(bool state = true) {
		if (layoutRoot){
			layoutRoot.Show(state);
		}
		if (m_Marker){
			m_Marker.Show(state);
		}
	}
	
	void OnDelete() {
		if (!m_deleted){
			m_deleted = true;
			Show(false);
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.Update);
		}
	}
	
	protected bool MarkerVisibleOnScreen() {
		if (m_MarkerData){
	        vector position = m_MarkerData.GetPosition();
	        vector screenPositionRelative = GetGame().GetScreenPosRelative(position);
	        if (screenPositionRelative[0] >= 1 || screenPositionRelative[0] == 0 || screenPositionRelative[1] >= 1 || screenPositionRelative[1] == 0)
	        {
	            return false;
	        }
	        else if (screenPositionRelative[2] < 0)
	        {
	            return false;
	        }
			return true;
		}
        return false;
    }
}