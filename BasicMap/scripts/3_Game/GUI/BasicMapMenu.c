ref BasicMapMenu m_BasicMapMenu;
bool m_BasicMapMenu_Opening = false;


class BasicMapMenu extends UIScriptedMenu
{	
	BasicMapMarker								m_SelectedMarker;
	
	protected int								m_logSkip = 200;
	
	protected int								m_CurrentListOffset = 0;
	
	static int 									MarkerListItemFrame_Size = 42;
	protected ref BasicMapMarker				m_MeMarker;
	
    protected ref BasicMapMarkerEditor 			m_MarkerEditor;
	
	protected string							m_CurGroup;
	protected int								m_CurGroupIndex;
	
	protected TextWidget						m_SelectedGroup;
	protected ButtonWidget						m_NextGroup;
	protected ButtonWidget						m_PreviousGroup;
	protected ref array<ref Widget>				m_MarkerListWidget;
	protected ref array<ref BasicMapMarkerListItem>	m_MarkerList;
	protected Widget 							m_MarkersListPanel;
	protected CheckBoxWidget 					m_ShowGroup3D;
	protected CheckBoxWidget 					m_ShowGroupMap;
	
	
	protected Widget							m_MarkerListTop;
	protected ButtonWidget						m_ScrollUp;
	
	protected Widget							m_MarkerListBottom;
	protected ButtonWidget						m_ScrollDown;
	
	protected TextWidget						m_PostionText;
	
	protected bool								m_PanelIsOpen = false; 
	protected bool								m_sidePanelOpen = false;
	protected bool								m_IsInitialized = false;
	
	
	protected Widget 							m_MapPanel;
	protected MapWidget							m_Map;
	
	protected Widget 							m_Expand;
	protected Widget							m_Minimize;
	
	protected Widget							m_ExpandPanel;
	
	protected Widget							m_Markers;
	
	protected TextWidget						m_InfoText;
	
	protected Widget							m_Editor;
	
	protected Widget							m_Show3dMakersPanel;
	protected CheckBoxWidget					m_Show3dMakers;
	
	
	protected ButtonWidget						m_BackToMe;
	
	override Widget Init()
    {
		
		layoutRoot 					= GetGame().GetWorkspace().CreateWidgets("BasicMap/gui/layouts/BasicMap.layout");
		
        m_MapPanel 					= Widget.Cast( layoutRoot.FindAnyWidget( "MapPanel" ) );
		
        m_Map 						= MapWidget.Cast( layoutRoot.FindAnyWidget( "Map" ) );
		
		m_ExpandPanel 				= Widget.Cast( layoutRoot.FindAnyWidget( "ExpandPanel" ) );
		
		m_Expand					= Widget.Cast( layoutRoot.FindAnyWidget( "Expand" ) );
		m_Minimize					= Widget.Cast( layoutRoot.FindAnyWidget( "Minimize" ) );
		
		
		m_SelectedGroup				= TextWidget.Cast( layoutRoot.FindAnyWidget( "CurrentGroup" ));
		m_NextGroup					= ButtonWidget.Cast(layoutRoot.FindAnyWidget("NextGroup"));
		m_PreviousGroup				= ButtonWidget.Cast(layoutRoot.FindAnyWidget("PreviousGroup"));
		m_MarkersListPanel			= Widget.Cast( layoutRoot.FindAnyWidget( "MarkersList" ) );
		m_MarkerListWidget 			= new ref array<ref Widget>;
		string MarkerFrame;
		for (int i = 0; i <= 17; i++){
			MarkerFrame = "MarkerFrame" + i;
			m_MarkerListWidget.Insert( Widget.Cast( layoutRoot.FindAnyWidget( MarkerFrame ) ) );
		}
		m_ShowGroup3D				= CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "ShowGroup3D" ) );
		m_ShowGroupMap				= CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "ShowGroupMap" ) );
		
		
		m_MarkerListTop				= Widget.Cast( layoutRoot.FindAnyWidget( "MarkerListTop" ) );
		m_ScrollUp					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ScrollUp" ) );
	
		m_MarkerListBottom			= Widget.Cast( layoutRoot.FindAnyWidget( "MarkerListBottom" ) );
		m_ScrollDown				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ScrollDown" ) );
		
		
		m_BackToMe					= ButtonWidget.Cast(layoutRoot.FindAnyWidget("BackToMe"));
		m_Show3dMakersPanel			= Widget.Cast( layoutRoot.FindAnyWidget( "Show3dMarkersPanel" ) );
		
		
		m_Show3dMakers				= CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "Show3dMakers" ) );
		m_Markers					= Widget.Cast( layoutRoot.FindAnyWidget( "Markers" ) );
		
		m_InfoText					= TextWidget.Cast( layoutRoot.FindAnyWidget( "InfoText" ));
		m_Editor					= Widget.Cast( layoutRoot.FindAnyWidget( "EditorFrame" ) ); 		
				
		m_PostionText				= TextWidget.Cast( layoutRoot.FindAnyWidget( "PostionText" ));
		
		Initialize();
		
		return layoutRoot;
    }


	void Initialize(){
		m_InfoText.SetText( BasicMap().GetInfoText() );
		
		if (ShowSelfOnMap()){
			m_BackToMe.Show(true);
		} else {
			m_BackToMe.Show(false);
		}
		
		m_Show3dMakersPanel.Show(GetBasicMapConfig().Allow3dMarkers);
		m_Show3dMakers.SetChecked(!BasicMap().ShowMarkersOnHUD());
		DayZPlayer me = DayZPlayer.Cast(GetGame().GetPlayer());
		BasicMapPlayerMarker playerMarker = new ref BasicMapPlayerMarker("", Vector(0,0,0));
		if (me){
			playerMarker.SetPlayer(me);
			if (ShowSelfOnMap()){
				SetMapPos(me.GetPosition());
			}
		}
		m_MeMarker = BasicMapPlayerMarker.Cast(playerMarker);
		if (BasicMap().ClientMarkers().Count() > 0){
			m_CurGroup = BasicMap().CLIENT_KEY;
		} else {
			m_CurGroup = BasicMap().SERVER_KEY;
		}
		m_CurGroupIndex = BasicMap().GetGroups().GetKeyArray().Find(m_CurGroup);
		m_SelectedGroup.SetText(BasicMap().GetGroupName(m_CurGroup));
		m_ShowGroup3D.SetChecked(BasicMap().GetGroup(m_CurGroup).OnHUD());
		m_ShowGroupMap.SetChecked(BasicMap().GetGroup(m_CurGroup).OnMap());
		PopulateMarkerList();
	}
	
	void SetMapPos(vector pos){
		m_Map.SetMapPos(pos);
	}
	
	void StepMarkerList(int i){
		m_CurGroupIndex = m_CurGroupIndex + i;
		if (m_CurGroupIndex < 0){
			m_CurGroupIndex = BasicMap().GetGroups().Count() - 1;
		}
		if (m_CurGroupIndex >= BasicMap().GetGroups().Count()){
			m_CurGroupIndex = 0;
		}
		m_CurGroup = BasicMap().GetGroups().GetKey(m_CurGroupIndex);
		m_SelectedGroup.SetText(BasicMap().GetGroupName(m_CurGroup));
		m_ShowGroup3D.SetChecked(BasicMap().GetGroup(m_CurGroup).OnHUD());
		m_ShowGroupMap.SetChecked(BasicMap().GetGroup(m_CurGroup).OnMap());
		m_CurrentListOffset = 0;
		PopulateMarkerList();
		
	}
	
	void PopulateMarkerList(){
		//Print("PopulateMarkerList Pre");
		ClearMarkerList();
		if (BasicMap().GetMarkers(m_CurGroup) && BasicMap().GetMarkers(m_CurGroup).Count() > 0){
			if (!m_MarkerList){
				m_MarkerList = new ref array<ref BasicMapMarkerListItem>;
			}
			//Print("PopulateMarkerList Start");
			int max = BasicMap().GetMarkers(m_CurGroup).Count() - 10;
			if (max > 0){
				while (m_CurrentListOffset > max && m_CurrentListOffset > 0){
					m_CurrentListOffset--;
				}
			}
			int i = 0;
			int i_M = m_CurrentListOffset;
			int maxItems = 17;
			while ( i_M < BasicMap().GetMarkers(m_CurGroup).Count() && i <= maxItems && i < m_MarkerListWidget.Count()){
				m_MarkerListWidget.Get(i).Show(true);
				m_MarkerList.Insert(new BasicMapMarkerListItem(m_MarkerListWidget.Get(i), this, BasicMap().GetMarkers(m_CurGroup).Get(i_M)));
				i++;
				i_M++;
			}
			if (m_MarkerList.Count() > 12){
				m_MarkerListBottom.Show(true);
			} else {
				m_MarkerListBottom.Show(false);
			}
			if (m_CurrentListOffset > 0){
				m_MarkerListTop.Show(true);
			} else {
				m_MarkerListTop.Show(false);
			}
			
			//Print("PopulateMarkerList End");
		}
		
	}
	
	protected void ClearMarkerList(){
		if (m_MarkerListWidget){
			for ( int j = 0; j < m_MarkerListWidget.Count(); j++){
				m_MarkerListWidget.Get(j).Show(false);
			}
		}
		if (m_MarkerList){
			for (int k = 0; k < m_MarkerList.Count(); k++){
				m_MarkerList.Get(k).Delete();
			}
			m_MarkerList.Clear();
		}
	}
	
	void UpdateMarkers(){
		m_Map.ClearUserMarks();
		for (int i = 0; i < BasicMap().Count(); i++) {
			BasicMapMarker marker = BasicMap().Marker(i);
			if (marker){
				marker.PrintDebug();
				if ( BasicMap().ShouldShowOnMap( marker.GetGroup() ) ){		
					float offset = 5.7;
					vector pos = marker.GetPosition();
					float x = pos[0] - offset; // Markers are a little off from the true postion
					m_Map.AddUserMark(Vector(x, pos[1],pos[2]), " " + marker.GetName(), marker.GetColour(), marker.GetIcon());
				}
			}
		}
		UpdateMe();
		if (m_PanelIsOpen){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateMarkers, 18, false);
		}
		RefreshMarkerList();
	}
	
    vector MapClickPosition(int x, int y) {
		vector pos = m_Map.ScreenToMap(Vector(x, y, 0));
		float X = pos[0] + 2.1; //Trying to correct marker being off . . . 
		float Z = pos[2] - 0.32;
		float Y = GetGame().SurfaceY(X, Z) + 0.4;
        return Vector(X, Y, Z);
    }
	
	
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) {
		vector clickPos = MapClickPosition(x,y);
		float radius = (m_Map.GetScale() * 110) + 5;
        if (w == m_Map && button == MouseState.LEFT) {
			int counter = 0;
			if (BasicMap().ClientMarkers()){
				counter = BasicMap().ClientMarkers().Count();
			}
			string name = "Mark - " + counter;
			if (!BasicMap().GetMarkerByVector(clickPos, radius)){
				if ( IsEditorOpen() ){
					CloseEditor();
				}
				if (GetBasicMapConfig().AllowPlayerMarkers && CanMakeMarkers()){
					Print("[BASICMAP] Creating Marker At " + clickPos);
		           	BasicMap().CreateMarker(m_CurGroup, name, clickPos);
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.PopulateMarkerList, 10, false);
					return true;
				}
			} else {
				if ( IsEditorOpen() ){
					CloseEditor();
				}
				m_SelectedMarker = BasicMapMarker.Cast( BasicMap().GetMarkerByVector(clickPos, radius) );
				Print("[BASICMAP] OpenEditor " + clickPos);
				OpenEditor(x, y);
				return true;
			}
		} else if (w == m_Map && button == MouseState.RIGHT) {
			BasicMapMarker marker = BasicMapMarker.Cast(BasicMap().GetMarkerByVector(clickPos, radius));
			bool IsDeletedMarkerSelected = false;
			if (marker && m_SelectedMarker == marker){
				IsDeletedMarkerSelected = true;
			}
			if (BasicMap().RemoveMarkerByVector(clickPos, radius)){
				if (IsDeletedMarkerSelected){
					CloseEditor();
				}
				if ( m_CurrentListOffset > 0){
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater( this.StepIconsList, 50, false, -1);
				} else {
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater( this.PopulateMarkerList, 50, false);
				}
				return true;
			}
        }
		return super.OnDoubleClick(w, x, y, button);
    }
	
	
	void UpdateMe(){
		if (ShowSelfOnMap()){
			m_Map.AddUserMark(m_MeMarker.GetPosition(), " ME", m_MeMarker.GetColour(), m_MeMarker.GetIcon());
			m_PostionText.SetText("Postion: " + m_MeMarker.GetPosition().ToString(true));
		}
	}
	
	void ~BasicMapMenu()
    {
		CloseEditor();
		BasicMap().OnMapClose();
		delete m_MeMarker;
		layoutRoot.Show(false);
    }
	
	bool IsOpen() {
		return m_PanelIsOpen;
	}

	void SetOpen(bool open) {
		if (!m_PanelIsOpen && open){
			layoutRoot.Show(true);
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateMarkers, 18, false);
		}
		if (m_PanelIsOpen && !open){
			CloseEditor();
			BasicMap().OnMapClose();
			delete m_MeMarker;
			layoutRoot.Show(false);
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
	
	//On click doesn't seem to work with map Widgets
	override bool OnMouseButtonDown(Widget w, int x, int y, int button ){
		//Print("[BASICMAP] OnMouseButtonDown " + w.GetName() + " X: " + x + " Y: " + y + " IsEditorOpen():" + IsEditorOpen() );
		
		if (w == m_Map && button == MouseState.LEFT && !IsEditorOpen()){
			vector clickPos = MapClickPosition(x,y);
			float radius = (m_Map.GetScale() * 110) + 5;
			if (BasicMap().GetMarkerByVector(clickPos, radius)){
				if ( IsEditorOpen() ){
					CloseEditor();
				}
				m_SelectedMarker = BasicMapMarker.Cast(BasicMap().GetMarkerByVector(clickPos, radius));
				if (m_SelectedMarker){
					//Print("[BASICMAP]" + m_SelectedMarker.GetName() + " Marker Found at " + clickPos);
					OpenEditor(x, y);
					return true;
				}
			} else {
				//Print("[BASICMAP] No Marker Found at " + clickPos);
			}
		}
		return super.OnMouseButtonDown(w, x, y, button );
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
		if (w == m_BackToMe){
			SetMapPos(m_MeMarker.GetPosition());
			return true;
		}
		if (w == m_NextGroup){
			StepMarkerList(1);
			return true;
		}
		if (w == m_PreviousGroup){
			StepMarkerList(-1);
			return true;
		}
		if (w == m_ScrollDown){
			StepIconsList(1);
			return true;
		}
		if (w == m_ScrollUp){
			StepIconsList(-1);
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
	
	void StepIconsList(int i){
		m_CurrentListOffset = m_CurrentListOffset + i;
		if (m_CurrentListOffset < 0){
			m_CurrentListOffset = 0;
		}
		int max = BasicMap().GetMarkers(m_CurGroup).Count() - 10;
		if (m_CurrentListOffset > max){
			m_CurrentListOffset = max;
		}
		PopulateMarkerList();
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (w == m_Show3dMakers){
			BasicMap().SetMarkersOnHUD(!m_Show3dMakers.IsChecked());
		}
		if (w == m_ShowGroup3D){
			BasicMap().GetGroup(m_CurGroup).SetOnHUD(m_ShowGroup3D.IsChecked());
		}
		if (w == m_ShowGroupMap){
			BasicMap().GetGroup(m_CurGroup).SetOnMap(m_ShowGroupMap.IsChecked());
		}
		
        return super.OnChange(w,x,y,finished);
	}
	
	void OpenEditor(int x, int y){
		if (m_SelectedMarker && CanMakeMarkers()){
			if (!m_MarkerEditor){
				m_MarkerEditor = new BasicMapMarkerEditor(m_Editor);
			}
			m_MarkerEditor.OpenEditor(x, y, m_SelectedMarker);
		} else {
			CloseEditor();
		}
	}
	
	void OpenEditorSelected(BasicMapMarker selectedMarker){
		if (selectedMarker){
			vector pos = m_Map.MapToScreen(selectedMarker.GetPosition());
			float x = pos[0];
			float y =  pos[1];
			int X = x; //CAN'T HAVE int X = pos[0]; or throws compiler error
			int Y = y; 
			m_SelectedMarker = BasicMapMarker.Cast(selectedMarker);
			OpenEditor(X, Y);
		}
	}
	
	void CloseEditor(){
		if (m_MarkerEditor){
			if (m_SelectedMarker){
				BasicMap().OnMarkerSave(m_SelectedMarker);
				m_SelectedMarker = NULL;
			}
			m_MarkerEditor.CloseEditor();
			delete m_MarkerEditor;
		}
		BasicMap().SaveClientMarkers();
	}
	
	bool IsEditorOpen(){
		if (m_MarkerEditor){
			return m_MarkerEditor.IsEditorOpen();
		}
		return false;
	}
	
	void RefreshMarkerList(){
		if (m_MarkerList){
			for (int i = 0; i < m_MarkerList.Count(); i++){
				if (m_MarkerList.Get(i)){
					if (m_MarkerList.Get(i).Refresh()){
					} else {
						GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_MarkerList.RemoveOrdered, 1, false, i);
					}
				}
			}
		}
	}
	
	
	void LockControls() {
		GetGame().GetMission().GetHud().ShowHudUI( false );
		GetGame().GetMission().GetHud().ShowQuickbarUI( false );
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_MOUSE_ALL);
        GetGame().GetUIManager().ShowUICursor(true);
    }

    void UnLockControls() {
		GetGame().GetMission().GetHud().ShowHudUI( true );
		GetGame().GetMission().GetHud().ShowQuickbarUI( true );
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
    }
	
	bool CanMakeMarkers(){
		if ( GetBasicMapConfig().RequirePenToMark && GetGame().IsClient() ){
			DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());

            if (player){
				array<EntityAI> itemsArray = new array<EntityAI>;
				player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);    	
                for (int i = 0; i < itemsArray.Count(); i++){
                    if (itemsArray.Get(i)){ 
						string itemType = itemsArray.Get(i).GetType();
						itemType.ToLower();
						if (itemType.Contains("pen_")){
                            return GetBasicMapConfig().AllowPlayerMarkers;
						}
                    }
                }
            }
			return false;
		} 
		return GetBasicMapConfig().AllowPlayerMarkers;
	}
	
	bool ShowSelfOnMap(){
		if ( GetBasicMapConfig().RequireCompassToSeeSelf && GetGame().IsClient() ){
			DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());

            if (player){
				array<EntityAI> itemsArray = new array<EntityAI>;
				player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);    	
                for (int i = 0; i < itemsArray.Count(); i++){
                    if (itemsArray.Get(i)){ 
						string itemType = itemsArray.Get(i).GetType();
						itemType.ToLower();
						if (itemType.Contains("compass")){
                            return GetBasicMapConfig().ShowSelfOnMap;
						}
                    }
                }
            }
			return false;
		} 
		return GetBasicMapConfig().ShowSelfOnMap;
	}
}