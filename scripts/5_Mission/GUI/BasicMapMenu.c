ref BasicMapMenu m_BasicMapMenu;
bool m_BasicMapMenu_Opening = false;

ref BasicMapMarker		m_SelectedMarker;

class BasicMapMenu extends UIScriptedMenu
{	
	
	protected Widget					m_Editor;
	
	protected EditBoxWidget				m_Editor_Name;
	
	protected ButtonWidget				m_Editor_Close;
	
	protected ImageWidget				m_Editor_Icon;
	protected ButtonWidget				m_Editor_IconRight;
	protected ButtonWidget				m_Editor_IconLeft;
	protected int						m_Editor_CurIcon = 0;	
	
	protected Widget					m_Editor_3DMaker;
	protected CheckBoxWidget			m_Editor_3DMakerBox;
	
	protected Widget					m_Editor_PartyMarker;
	protected CheckBoxWidget			m_Editor_PartyMarkerBox;
		
	protected SliderWidget				m_Editor_Colour_Red;
	protected SliderWidget				m_Editor_Colour_Green;
	protected SliderWidget				m_Editor_Colour_Blue;
	protected SliderWidget				m_Editor_Colour_Alpha;
	
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
		
		m_Editor 					= Widget.Cast(layoutRoot.FindAnyWidget( "Editor" ));
	
		m_Editor_Name 				=  EditBoxWidget.Cast(layoutRoot.FindAnyWidget( "Name" ));
	
		m_Editor_Close 				= ButtonWidget.Cast(layoutRoot.FindAnyWidget( "Close" ));
	
		m_Editor_Icon 				= ImageWidget.Cast(layoutRoot.FindAnyWidget( "Icon" ));
		m_Editor_IconRight 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget( "Right" ));
		m_Editor_IconLeft 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget( "Left" ));
		
		m_Editor_3DMaker = Widget.Cast(layoutRoot.FindAnyWidget( "ThreeDMarkerPanel" ));
		m_Editor_3DMakerBox = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget( "ThreeDMarker" ));
	
		m_Editor_PartyMarker = Widget.Cast(layoutRoot.FindAnyWidget( "PartyMarkerPanel" ));
		m_Editor_PartyMarkerBox = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget( "PartyMarker" ));
		
		m_Editor_Colour_Red = SliderWidget.Cast(layoutRoot.FindAnyWidget( "Red" ));
		m_Editor_Colour_Green = SliderWidget.Cast(layoutRoot.FindAnyWidget( "Green" ));
		m_Editor_Colour_Blue = SliderWidget.Cast(layoutRoot.FindAnyWidget( "Blue" ));
		m_Editor_Colour_Alpha = SliderWidget.Cast(layoutRoot.FindAnyWidget( "Alpha" ));
		
        WidgetEventHandler.GetInstance().RegisterOnDoubleClick( m_Map, this, "OnMapDoubleClick" );
		
		m_Editor.Show(false);
		
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
			m_SelectedMarker = BasicMap().GetClientMarkerByVector(clickPos, radius);
			if (!m_SelectedMarker){
	            BasicMap().AddClientMarker( new ref BasicMapMarker(name, "BasicMap\\gui\\images\\marker.paa", clickPos, {119, 136, 198}, 190, true));
	        	BasicMap().SaveClientMarkers();
			} else {
				if (m_sidePanelOpen){
					OpenEditor();
				}
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
		m_ExpandPanel.Show(false);
		m_MapPanel.SetSize(0.82,1);
		m_Markers.SetSize(0.18,1);
		m_Markers.Show(true);
	}
	
	void Minimize(){
		m_sidePanelOpen = false;
		CloseEditor();
		m_ExpandPanel.Show(true);
		m_MapPanel.SetSize(0.988,1);
		m_Markers.Show(false);
		m_Markers.SetSize(0,1);

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
		if (w == m_Editor_Close){
			CloseEditor();
			return true;
		}
		if (w == m_Editor_3DMakerBox){
			m_SelectedMarker.ShowOnHUD(m_Editor_3DMakerBox.IsChecked());
			return true;
		}
		if (w == m_Editor_IconRight){
			StepIcon(1);
		}
		if (w == m_Editor_IconLeft){
			StepIcon(-1);
		}
		return super.OnClick(w, x, y, button);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (w == m_Editor_Colour_Red){
			m_SelectedMarker.Colour[0] = m_Editor_Colour_Red.GetCurrent();
			RefreshEditorIcon();
		}
		if (w ==  m_Editor_Colour_Green){
			m_SelectedMarker.Colour[1] = m_Editor_Colour_Green.GetCurrent();
			RefreshEditorIcon();
		}
		if (w == m_Editor_Colour_Blue){
			m_SelectedMarker.Colour[2] = m_Editor_Colour_Blue.GetCurrent();
			RefreshEditorIcon();
		}
		if (w == m_Editor_Colour_Alpha){
			m_SelectedMarker.Alpha = m_Editor_Colour_Alpha.GetCurrent();
			RefreshEditorIcon();
		}
		if (w == m_Editor_Name){
			m_SelectedMarker.Name = m_Editor_Name.GetText();
			m_Editor_Name.SetText(m_SelectedMarker.GetName());
		}
        return super.OnChange(w,x,y,finished);
	}
	void StepIcon(int dir){
		m_Editor_CurIcon = m_Editor_CurIcon + dir;
		if (m_Editor_CurIcon < 0){
			m_Editor_CurIcon = GetBasicMapConfig().Icons.Count() - 1;
		} else if (m_Editor_CurIcon >= GetBasicMapConfig().Icons.Count() ){
			m_Editor_CurIcon = 0;
		}
		m_Editor_Icon.LoadImageFile(0,  GetBasicMapConfig().Icons.Get(m_Editor_CurIcon));
		m_SelectedMarker.Icon = GetBasicMapConfig().Icons.Get(m_Editor_CurIcon);
	}
	
	
	void RefreshEditorIcon(){
		m_Editor_Icon.SetColor(m_SelectedMarker.GetColour());
	}
	
	void OpenEditor(){
		if (m_SelectedMarker){
			m_EditorIsOpen = true;
			m_Editor.Show(true);
			int red = m_SelectedMarker.Colour[0];
			int blue = m_SelectedMarker.Colour[1];
			int green = m_SelectedMarker.Colour[2];
			int alpha = m_SelectedMarker.Alpha;
			m_Editor_Colour_Red.SetCurrent(red);
			m_Editor_Colour_Green.SetCurrent(blue);
			m_Editor_Colour_Blue.SetCurrent(green);
			m_Editor_Colour_Alpha.SetCurrent(alpha);
			
			m_Editor_Icon.LoadImageFile(0, m_SelectedMarker.Icon);
			
			m_Editor_CurIcon = GetBasicMapConfig().Icons.Find(m_SelectedMarker.Icon);
			
			m_Editor_Name.SetText(m_SelectedMarker.GetName());
			m_Editor_3DMakerBox.SetChecked(m_SelectedMarker.OnHUD());
			RefreshEditorIcon();
		} else {
			m_Editor.Show(false);
		}
	}
	
	void CloseEditor(){
		m_EditorIsOpen = false;
		m_Editor.Show(false);
		m_Editor_Name.SetText("");
		m_Editor_Colour_Red.SetCurrent(150);
		m_Editor_Colour_Green.SetCurrent(150);
		m_Editor_Colour_Blue.SetCurrent(150);
		m_Editor_Colour_Alpha.SetCurrent(150);
		BasicMap().SaveClientMarkers();
	}
	
	bool IsEditorOpen(){
		return m_EditorIsOpen;
	}
	
}