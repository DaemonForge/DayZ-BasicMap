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
		m_Distance.SetColor(m_MarkerData.GetColour());
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
		if (m_MarkerData && layoutRoot){
			if (MarkerVisibleOnScreen() && m_MarkerData.OnHUD() && BasicMap().ShowMarkersOnHUD() && BasicMap().ShouldShowOnHUD(m_MarkerData.GetGroup()) ){
				
				float x;
				float y;
				vector screenPosition = GetGame().GetScreenPos(m_MarkerData.GetPosition());
				x = Math.Round(screenPosition[0]);
		        y = Math.Round(screenPosition[1]);
				
				if (m_MarkerData.ShowDistance()){
					m_Distance.Show(true);
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
				} else {
					m_Distance.Show(false);
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
		} else {
			OnDelete();
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