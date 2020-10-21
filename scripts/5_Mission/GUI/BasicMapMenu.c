ref BasicMapMenu m_BasicMapMenu;
bool m_BasicMapMenu_Opening = false;

class BasicMapMenu extends UIScriptedMenu
{	
	protected bool						m_PanelIsOpen = false; 
	protected bool						m_IsInitialized = false;
	
	protected Widget 					m_MapPanel;
	protected MapWidget					m_Map;
	
	protected Widget 					m_Expand;
	protected Widget					m_Minimize;
	
	protected Widget					m_ExpandPanel;
	
	protected Widget					m_Markers;
		
	override Widget Init()
    {
		if (!m_IsInitialized){
			Initialize();
		}
		
		layoutRoot 					= GetGame().GetWorkspace().CreateWidgets("BasicMap/gui/layouts/BasicMap.layout");
		
        m_MapPanel 					= Widget.Cast( layoutRoot.FindAnyWidget( "MapPanel" ) );
        m_Map 						= MapWidget.Cast( layoutRoot.FindAnyWidget( "Map" ) );
		
		m_Expand					= Widget.Cast( layoutRoot.FindAnyWidget( "Expand" ) );
		m_Minimize					= Widget.Cast( layoutRoot.FindAnyWidget( "Minimize" ) );
		
		
		m_Markers					= Widget.Cast( layoutRoot.FindAnyWidget( "Markers" ) );
		
		m_ExpandPanel				= Widget.Cast( layoutRoot.FindAnyWidget( "ExpandPanel" ) );
		
		
		
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick( m_Map, this, "OnMapDoubleClick" );
		
		return layoutRoot;
    }

	void Initialize(){
		m_IsInitialized = true;
	}
	
	void UpdateMarkers(){
		m_Map.ClearUserMarks();
		for (int i = 0; i < BasicMap().Count(); i++) {
			BasicMapMarker marker = BasicMap().Marker(i);
			float offset = 5.7;
			vector pos = marker.GetPosition();
			float x = pos[0] - offset; // Markers are a little off from the true postion
			m_Map.AddUserMark(Vector(x, pos[1],pos[2]), " " + marker.GetName(), marker.GetColour(), marker.Icon);
		}
		UpdateMe();
		if (m_PanelIsOpen){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateMarkers, 18, false);
		}
	}
	
	//Returns world coords of where player clicks on map
    vector MapClickPosition(int x, int y) {
		vector pos = m_Map.ScreenToMap(Vector(x, y, 0));
		float X = pos[0] + 2.1; //Trying to correct marker being off . . . 
		float Z = pos[2] - 0.32;
		float Y = GetGame().SurfaceY(X, Z) + 0.4;
        return Vector(X, Y, Z);
    }
	void OnMapDoubleClick(Widget w, int x, int y, int button) {
		vector clickPos = MapClickPosition(x,y);
		float radius = (m_Map.GetScale() * 95) + 5;
		Print("Scale: " + m_Map.GetScale() + " Radius: " + radius + " ClickPos: " + clickPos);
        if (button == MouseState.LEFT) {
			string name = "Mark - " + BasicMap().ClientMarkers.Count();
			if (!BasicMap().GetClientMarkerByVector(clickPos, radius)){
	            BasicMap().AddClientMarker( new ref BasicMapMarker(name, "BasicMap\\gui\\images\\marker.paa", clickPos, {119, 136, 198}, 190, true));
	        	BasicMap().SaveClientMarkers();
			} else {
				//Open EditDialog
			}
		} else if (button == MouseState.RIGHT) {
			if (BasicMap().RemoveClientMarkerByVector(clickPos, radius)){
				BasicMap().SaveClientMarkers();
			}
        }
    }
	
	void UpdateMe(){
		PlayerBase me = PlayerBase.Cast(GetGame().GetPlayer());
		if (me){
			m_Map.AddUserMark(me.GetPosition(), " ME", ARGB(230, 33, 233, 255), "BasicMap\\gui\\images\\me.paa");
		}
	}
	
	void ~BasicMapMenu()
    {
		layoutRoot.Show(false);
    }
	
	bool IsOpen() {
		return m_PanelIsOpen;
	}

	void SetOpen(bool open) {
		if (!m_PanelIsOpen && open){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateMarkers, 18, false);
		}
		m_PanelIsOpen = open;
	}
	
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		if (w == m_Expand){
			m_ExpandPanel.Show(false);
			m_MapPanel.SetSize(0.82,1);
			m_Markers.SetSize(0.18,1);
			m_Markers.Show(true);
			return true;
		}
		if (w == m_Minimize){
			m_ExpandPanel.Show(true);
			m_MapPanel.SetSize(0.988,1);
			m_Markers.Show(false);
			m_Markers.SetSize(0,1);
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
        return super.OnChange(w,x,y,finished);
	}
}