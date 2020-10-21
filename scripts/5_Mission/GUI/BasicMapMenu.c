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
			m_Map.AddUserMark(marker.GetPosition(), " " + marker.GetName(), marker.GetColour(), marker.Icon);
		}
		UpdateMe();
		if (m_PanelIsOpen){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateMarkers, 18, false);
		}
	}
	
	//Returns world coords of where player clicks on map
    vector MapClickPosition() {
		vector pointerPos = GetGame().GetPointerDirection();;
		vector cameraPos = GetGame().GetCurrentCameraPosition();
		vector calcPos = cameraPos + ( pointerPos * 1000 );
		vector pos = m_Map.ScreenToMap( GetGame().GetScreenPos( calcPos ) );
		Print("Pos: " + pos);
		float y = GetGame().SurfaceY(pos[0], pos[2]) + 0.3;
        return Vector(pos[0], y, pos[2]);
    }
	
	void OnMapDoubleClick(Widget w, int x, int y, int button) {
		vector clickPos = MapClickPosition();
		float radius = (m_Map.GetScale() * 95) + 5;
		Print("Scale: " + m_Map.GetScale() + " Radius: " + radius + " ClickPos: " + clickPos);
        if (button == MouseState.LEFT) {
			string name = "Mark - " + BasicMap().ClientMarkers.Count();
			if (!BasicMap().GetClientMarkerByVector(clickPos, radius)){
	            BasicMap().AddClientMarker( new ref BasicMapMarker(name, "BasicMap\\gui\\images\\marker.paa", MapClickPosition(), {119, 136, 198}, 150, true));
	        	BasicMap().SaveClientMarkers();
			}
		} else if (button == MouseState.RIGHT) {
			if (BasicMap().RemoveClientMarkerByVector(MapClickPosition(), radius)){
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