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
		
		
		
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick( m_Map, this, "DoubleClick" );
		UpdateMarkers();
		return layoutRoot;
    }

	void Initialize(){
		m_IsInitialized = true;
	}
	
	void UpdateMarkers(){
		m_Map.ClearUserMarks();
		for (int i = 0; i < BasicMap().Count(); i++) {
			BasicMapMarker marker = BasicMap().Marker(i);
			m_Map.AddUserMark(marker.GetPosition(),marker.Name, marker.GetColour(), marker.Icon);
		}
		UpdateMe();
	}
	
	void DoubleClick(Widget w, int x, int y, int button) {
        if (button == MouseState.LEFT) {
            
        } else if (button == MouseState.RIGHT) {
			
        }
    }
	
	void UpdateMe(){
		PlayerBase me = PlayerBase.Cast(GetGame().GetPlayer());
		if (me){
			m_Map.AddUserMark(me.GetPosition(), " Me", ARGB(230, 33, 233, 255), "BasicMap\\gui\\images\\me.paa");
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