ref BasicMapMenu m_BasicMapMenu;
bool m_BasicMapMenu_Opening = false;

ref BasicMapMarker		m_SelectedMarker;

class BasicMapMenu extends UIScriptedMenu
{	
	protected ref BasicMapMarker		m_MeMarker;
	
    protected ref BasicMapMarkerEditor 	m_MarkerEditor;
	
	
	protected bool						m_EditorIsOpen = false;
	protected bool						m_PanelIsOpen = false; 
	protected bool						m_sidePanelOpen = false;
	protected bool						m_IsInitialized = false;
	
	
	protected Widget 					m_MapPanel;
	protected MapWidget					m_Map;
	
	protected Widget 					m_Expand;
	protected Widget					m_Minimize;
	
	protected Widget					m_ExpandPanel;
	
	protected Widget					m_Markers;
	
	protected TextWidget				m_InfoText;
	
	protected Widget					m_Editor;
	
	override Widget Init()
    {
		
		layoutRoot 					= GetGame().GetWorkspace().CreateWidgets("BasicMap/gui/layouts/BasicMap.layout");
		
        m_MapPanel 					= Widget.Cast( layoutRoot.FindAnyWidget( "MapPanel" ) );
		
        m_Map 						= MapWidget.Cast( layoutRoot.FindAnyWidget( "Map" ) );
		
		m_ExpandPanel 				= Widget.Cast( layoutRoot.FindAnyWidget( "ExpandPanel" ) );
		
		m_Expand					= Widget.Cast( layoutRoot.FindAnyWidget( "Expand" ) );
		m_Minimize					= Widget.Cast( layoutRoot.FindAnyWidget( "Minimize" ) );
		
		
		m_Markers					= Widget.Cast( layoutRoot.FindAnyWidget( "Markers" ) );
		
		m_InfoText					= TextWidget.Cast( layoutRoot.FindAnyWidget( "InfoText" ));
		m_Editor					= Widget.Cast( layoutRoot.FindAnyWidget( "EditorFrame" ) ); 			
		
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick( m_Map, this, "OnMapDoubleClick" );
		
		m_InfoText.SetText( BasicMap().GetInfoText() );
		
		ref BasicMapPlayerMarker meMarker = new ref BasicMapPlayerMarker("", Vector(0,0,0));
		PlayerBase me = PlayerBase.Cast(GetGame().GetPlayer());
		if (me){
			meMarker.SetPlayer(me);
		}
		m_MeMarker = meMarker;
		
		if (!m_IsInitialized){
			Initialize();
		}
		
		return layoutRoot;
    }

	void Initialize(){
		m_IsInitialized = true;
		PlayerBase me = PlayerBase.Cast(GetGame().GetPlayer());
		if (me){
			m_Map.SetMapPos(me.GetPosition());
		}
	}
	
	void UpdateMarkers(){
		m_Map.ClearUserMarks();
		for (int i = 0; i < BasicMap().Count(); i++) {
			BasicMapMarker marker = BasicMap().Marker(i);
			float offset = 5.7;
			vector pos = marker.GetPosition();
			float x = pos[0] - offset; // Markers are a little off from the true postion
			m_Map.AddUserMark(Vector(x, pos[1],pos[2]), " " + marker.GetName(), marker.GetColour(), marker.GetIcon());
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
		float radius = (m_Map.GetScale() * 110) + 5;
		Print("Scale: " + m_Map.GetScale() + " Radius: " + radius + " ClickPos: " + clickPos);
        if (button == MouseState.LEFT) {
			int counter = 0;
			if (BasicMap().ClientMarkers()){
				counter = BasicMap().ClientMarkers().Count();
			}
			string name = "Mark - " + counter;
			m_SelectedMarker = BasicMap().GetMarkerByVector(clickPos, radius);
			if (!m_SelectedMarker){
				CloseEditor();
	            BasicMap().AddClientMarker( new ref BasicMapMarker(name, clickPos, "BasicMap\\gui\\images\\marker.paa", {119, 136, 198}, 190, true));
	        	BasicMap().SaveClientMarkers();
			} else {
				OpenEditor(x, y);
			}
		} else if (button == MouseState.RIGHT) {
			BasicMapMarker marker = BasicMap().GetMarkerByVector(clickPos, radius);
			bool IsDeletedMarkerSelected = false;
			if (marker == m_SelectedMarker){
				IsDeletedMarkerSelected = true;
			}
			if (BasicMap().RemoveMarkerByVector(clickPos, radius)){
				if (IsDeletedMarkerSelected){
					CloseEditor();
				}
				BasicMap().SaveClientMarkers();
			}
        }
    }
	
	void UpdateMe(){
		m_Map.AddUserMark(m_MeMarker.GetPosition(), " ME", ARGB(230, 33, 233, 255), m_MeMarker.GetIcon());
	}
	
	void ~BasicMapMenu()
    {
		layoutRoot.Show(false);
		CloseEditor();
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
	
	void Expand(){
		m_sidePanelOpen = true;
		m_MapPanel.SetSize(0.82,1);
		m_ExpandPanel.Show(false);
		m_Markers.Show(true);
	}
	
	void Minimize(){
		m_sidePanelOpen = false;
		m_MapPanel.SetSize(0.988,1);
		m_ExpandPanel.Show(true);
		m_Markers.Show(false);
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		if (w == m_Expand){
			Expand();
			return true;
		}
		if (w == m_Minimize){
			Minimize();
			return true;
		}			
		return super.OnClick(w, x, y, button);
	}
	
	
	void OpenEditor(int x, int y){
		if (m_SelectedMarker){
			m_EditorIsOpen = true;
			if (!m_MarkerEditor){
				m_MarkerEditor = new BasicMapMarkerEditor(m_Editor);
			}
			m_Editor.Show(true);
			m_MarkerEditor.OpenEditor(x, y);
		} else {
			m_Editor.Show(false);
			m_MarkerEditor.CloseEditor();
		}
	}
	
	void CloseEditor(){
		m_EditorIsOpen = false;
		if (m_MarkerEditor){
			m_MarkerEditor.CloseEditor();
		}
		BasicMap().SaveClientMarkers();
	}
	
	bool IsEditorOpen(){
		return m_EditorIsOpen;
	}
	
}