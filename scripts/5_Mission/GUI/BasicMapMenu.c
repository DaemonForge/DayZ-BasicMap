ref BasicMapMenu m_BasicMapMenu;
bool m_BasicMapMenu_Opening = false;

class BasicMapMenu extends UIScriptedMenu
{	
	protected bool						m_PanelIsOpen = false; 
	protected bool						m_IsInitialized = false;
	
	protected MapWidget					m_Map;
	
	protected Widget 					m_Expand;
	protected Widget					m_Minimize;
	
	protected Widget					m_Markers;
		
	override Widget Init()
    {
		if (!m_IsInitialized){
			Initialize();
		}
		
		layoutRoot 					= GetGame().GetWorkspace().CreateWidgets("BasicMap/gui/layouts/BasicMap.layout");
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
			m_Map.AddUserMark(me.GetPosition(), "Me", ARGB(230,44,149,163), "BasicMap\\gui\\images\\me.paa");
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
			m_Markers.Show(true);
			return true;
		}
		if (w == m_Minimize){
			m_ExpandPanel.Show(true);
			m_Markers.Show(false);
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
        return super.OnChange(w,x,y,finished);
	}
}