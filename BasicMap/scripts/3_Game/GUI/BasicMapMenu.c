ref BasicMapMenu m_BasicMapMenu;
bool m_BasicMapMenu_Opening = false;


class BasicMapMenu extends UIScriptedMenu
{	
	BasicMapMarker								m_SelectedMarker;
	
	protected int								m_logSkip = 200;
	
	protected int								m_CurrentListOffset = 0;
	
	static int									m_MarkerRefreshRate = 30;
	
	static int 								MarkerListItemFrame_Size = 38;
	protected autoptr BasicMapMarker			m_MeMarker;
	
    protected autoptr BasicMapMarkerEditor 	m_MarkerEditor;
	
    protected autoptr BasicMapRightClick 		m_RightClickMenu;
	
	protected string							m_CurGroup;
	protected int								m_CurGroupIndex;
	
	protected TextWidget						m_SelectedGroup;
	protected ButtonWidget						m_NextGroup;
	protected ButtonWidget						m_PreviousGroup;
	protected autoptr array<Widget>			m_MarkerListWidget;
	protected autoptr array<autoptr BasicMapMarkerListItem>	m_MarkerList;
	protected Widget 							m_MarkersListPanel;
	protected CheckBoxWidget 					m_ShowGroup3D;
	protected CheckBoxWidget 					m_ShowGroupMap;
	
	
	protected Widget							m_MarkerListTop;
	protected ButtonWidget						m_ScrollUp;
	
	protected Widget							m_MarkerListBottom;
	protected ButtonWidget						m_ScrollDown;
	
	protected TextWidget						m_PostionText;

	protected bool								m_PanelIsOpen = false; 
	protected bool								m_IsInitialized = false;	
	protected Widget 							m_MapPanel;
	protected Widget 							m_MapFrame;
	protected MapWidget						m_Map;
	
	protected TextWidget						m_InfoText;
	
	protected Widget							m_Editor;
	
	protected Widget							m_Show3dMakersPanel;
	protected CheckBoxWidget					m_Show3dMakers;
	
	
	protected ButtonWidget						m_BackToMe;
	protected Widget							m_ContentArea;
	
	override Widget Init()
    {
		
		layoutRoot 					= Widget.Cast(  GetGame().GetWorkspace().CreateWidgets("BasicMap/gui/layouts/BasicMap.layout"));
		
        m_MapPanel 					= Widget.Cast( layoutRoot.FindAnyWidget( "MapPanel" ) );
		
		m_MapFrame					= Widget.Cast( layoutRoot.FindAnyWidget( "MapFrame" ) );
		
        m_Map 						= MapWidget.Cast( layoutRoot.FindAnyWidget( "Map" ) );
		
		m_ContentArea				= Widget.Cast( layoutRoot.FindAnyWidget( "ContentArea" ) );
		
		m_SelectedGroup				= TextWidget.Cast( layoutRoot.FindAnyWidget( "CurrentGroup" ));
		m_NextGroup					= ButtonWidget.Cast(layoutRoot.FindAnyWidget("NextGroup"));
		m_PreviousGroup				= ButtonWidget.Cast(layoutRoot.FindAnyWidget("PreviousGroup"));
		m_MarkersListPanel			= Widget.Cast( layoutRoot.FindAnyWidget( "MarkersList" ) );
		m_MarkerListWidget 			= new array<Widget>;
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

		
		m_InfoText					= TextWidget.Cast( layoutRoot.FindAnyWidget( "InfoText" ));
		m_Editor					= Widget.Cast( layoutRoot.FindAnyWidget( "EditorFrame" ) ); 		
				
		m_PostionText				= TextWidget.Cast( layoutRoot.FindAnyWidget( "PostionText" ));
		
		Initialize();
		
		// Schedule content area resize after layout is created
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateContentAreaSize, 100, false);
		
		return layoutRoot;
    }


	void Initialize(){
		m_InfoText.SetText( BasicMap().GetInfoText() );
		
		if (BasicMap().ShowSelfOnMap()){
			m_BackToMe.Show(true);
		} else {
			m_BackToMe.Show(false);
		}
		
		m_Show3dMakersPanel.Show(GetBasicMapConfig().Allow3dMarkers);
		m_Show3dMakers.SetChecked(!BasicMap().ShowMarkersOnHUD());
		DayZPlayer me = DayZPlayer.Cast(GetGame().GetPlayer());
		BasicMapPlayerMarker playerMarker = new BasicMapPlayerMarker("", Vector(0,0,0));
		if (me){
			playerMarker.SetPlayer(me);
			if (BasicMap().ShowSelfOnMap()){
				SetMapPos(me.GetPosition());
			}
		}
		m_MeMarker = BasicMapPlayerMarker.Cast(playerMarker);
		if (BasicMap().ClientMarkers() && BasicMap().ClientMarkers().Count() > 0){
			m_CurGroup = BasicMap().CLIENT_KEY;
		} else {
			m_CurGroup = BasicMap().SERVER_KEY;
		}
		m_CurGroupIndex = BasicMap().GetGroups().GetKeyArray().Find(m_CurGroup);
		if (m_SelectedGroup) m_SelectedGroup.SetText(BasicMap().GetGroupName(m_CurGroup));
		if (m_ShowGroup3D) m_ShowGroup3D.SetChecked(BasicMap().GetGroup(m_CurGroup).OnHUD());
		if (m_ShowGroupMap) m_ShowGroupMap.SetChecked(BasicMap().GetGroup(m_CurGroup).OnMap());
		PopulateMarkerList();
		vector lastLookPos;
		float lastLookZoom;
		if (BasicMap().GetLastLook(lastLookPos,lastLookZoom)){
			m_Map.SetScale(lastLookZoom);
			m_Map.SetMapPos(lastLookPos);
		}
	}
	
	void SetMapPos(vector pos){
		m_Map.SetMapPos(pos);
	}
	
	// Dynamically size the ContentArea to fit between header (40px) and footer (40px)
	// This ensures the footer bar with "Find Me" button is always visible at all resolutions
	void UpdateContentAreaSize()
	{
		if (!m_ContentArea || !m_MapPanel) return;
		
		// Get the MapPanel's actual screen size
		float panelW, panelH;
		m_MapPanel.GetScreenSize(panelW, panelH);
		
		if (panelH <= 80) return;
		
		// Header is 40px, Footer is 40px = 80px total to subtract
		float headerHeight = 40;
		float footerHeight = 40;
		float contentHeight = panelH - headerHeight - footerHeight;
		
		// ContentArea layout has: hexactsize 0 (width relative), vexactsize 1 (height pixel)
		// So SetSize width should be relative (1.0 = 100%), height should be pixel value
		m_ContentArea.SetSize(1.0, contentHeight);
	}
	
	override void OnShow()
	{
		super.OnShow();
		// Recalculate content area size when menu is shown
		// Call immediately and also with a slight delay to ensure layout is settled
		UpdateContentAreaSize();
		// Delayed call ensures the layout engine has fully calculated sizes
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateContentAreaSize, 50, false);
	}

	override void OnHide()
	{
		// This menu can be closed/hidden by multiple paths (hotkey, ESC, UIManager).
		// Make sure we always restore player controls and close any sub-widgets.
		CloseRightClick();
		CloseEditor();
		SetOpen(false);
		UnLockControls();
		super.OnHide();
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
		if (m_SelectedGroup) m_SelectedGroup.SetText(BasicMap().GetGroupName(m_CurGroup));
		if (m_ShowGroup3D) m_ShowGroup3D.SetChecked(BasicMap().GetGroup(m_CurGroup).OnHUD());
		if (m_ShowGroupMap) m_ShowGroupMap.SetChecked(BasicMap().GetGroup(m_CurGroup).OnMap());
		m_CurrentListOffset = 0;
		PopulateMarkerList();
		
	}
	
	void PopulateMarkerList(){
		//Print("PopulateMarkerList Pre");
		ClearMarkerList();
		if (!m_MarkerListWidget || m_MarkerListWidget.Count() == 0) return;
		if (BasicMap().GetMarkers(m_CurGroup) && BasicMap().GetMarkers(m_CurGroup).Count() > 0){
			if (!m_MarkerList){
				m_MarkerList = new array<autoptr BasicMapMarkerListItem>;
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
				if (BasicMap().GetMarkers(m_CurGroup).Get(i_M) && BasicMap().GetMarkers(m_CurGroup).Get(i_M).OnPanel() && BasicMap().GetMarkers(m_CurGroup).Get(i_M).OnMap()){
					if (m_MarkerListWidget.Get(i)) {
						m_MarkerListWidget.Get(i).Show(true);
						m_MarkerList.Insert(new BasicMapMarkerListItem(m_MarkerListWidget.Get(i), this, BasicMap().GetMarkers(m_CurGroup).Get(i_M)));
					}
					i++;
				}
				i_M++;
			}
			if (m_MarkerListBottom) {
				if (m_MarkerList.Count() > 12){
					m_MarkerListBottom.Show(true);
				} else {
					m_MarkerListBottom.Show(false);
				}
			}
			if (m_MarkerListTop) {
				if (m_CurrentListOffset > 0){
					m_MarkerListTop.Show(true);
				} else {
					m_MarkerListTop.Show(false);
				}
			}
			
			//Print("PopulateMarkerList End");
		}
		
	}
	
	protected void ClearMarkerList(){
		if (m_MarkerListWidget){
			for ( int j = 0; j < m_MarkerListWidget.Count(); j++){
				if (m_MarkerListWidget.Get(j)) m_MarkerListWidget.Get(j).Show(false);
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
		int markerCount = 0;
		if (m_PanelIsOpen && m_Map && BasicMap()){
			BasicMap().SetLastLook(m_Map.GetMapPos(),m_Map.GetScale());
			m_Map.ClearUserMarks();
			for (int i = 0; i < BasicMap().Count(); i++) {
				BasicMapMarker marker = BasicMapMarker.Cast(BasicMap().Marker(i));
				if (marker && marker.OnMap()){
					bool ShowOnMap = !(marker.GetGroup());
					ShowOnMap = (ShowOnMap || !(BasicMap().GetGroups()));
					ShowOnMap = (ShowOnMap || !(BasicMap().GetGroups().Get(marker.GetGroup())));
					ShowOnMap = (ShowOnMap || BasicMap().GetGroups().Get(marker.GetGroup()).OnMap());
					if ( ShowOnMap ) {		
						float offset = 5.7;
						vector pos = marker.GetPosition();
						float x = pos[0] - offset; // Markers are a little off from the true postion
						BasicMapCircleMarker cMarker;
						if (marker.IsInherited(BasicMapCircleMarker) && Class.CastTo(cMarker, marker) && cMarker.GetRadius() > 0){
							array<vector> edge;
							if ( cMarker.GetGroup() && BasicMap().GetMarkers( cMarker.GetGroup() ) ){
							 	edge = cMarker.GetEdge( BasicMap().GetMarkers( cMarker.GetGroup() ) );
							} else {
								edge =  cMarker.GetEdge();
							}
							if (edge){
								for ( int j = 0; j < edge.Count(); j++){
									markerCount++;
									string edgeIcon = GetSafeIconPath(cMarker.GetEdgeIcon(m_Map.GetScale()));
									m_Map.AddUserMark(edge.Get(j), "" , cMarker.GetEdgeColour(), edgeIcon);
								}
							}
							if (cMarker.GetShowCenterMarker()){
								markerCount++;
								string cIcon = GetSafeIconPath(marker.GetIcon());
								m_Map.AddUserMark(Vector(x, pos[1],pos[2]), " " + marker.GetName(), marker.GetColour(), cIcon);	
							}
						} else {
							markerCount++;
							string icon = GetSafeIconPath(marker.GetIcon());
							m_Map.AddUserMark(Vector(x, pos[1],pos[2]), " " + marker.GetName(), marker.GetColour(), icon);
						}
					}
				}
			}
			UpdateMe();
			RefreshMarkerList();
			int RefreshRate = m_MarkerRefreshRate;
			if (markerCount > 500){
				int bonusRate = Math.Floor(markerCount / 500);
				RefreshRate = RefreshRate + ( bonusRate * 5 );
			}
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateMarkers, RefreshRate, false);
		}
	}

	protected string GetSafeIconPath(string iconIn)
	{
		string icon = iconIn;
		if (!icon || icon == "" || icon == " ")
		{
			icon = "BasicMap\\gui\\images\\marker.paa";
		}
		// Replace .edds with .paa if present (MapWidget doesn't support .edds)
		icon.Replace(".edds", ".paa");
		return icon;
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
					//Print("[BASICMAP] Creating Marker At " + clickPos);
		           	BasicMap().CreateMarker(m_CurGroup, name, clickPos);
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.PopulateMarkerList, 10, false);
					return true;
				}
			} else {
				if ( IsEditorOpen() ){
					CloseEditor();
				}
				m_SelectedMarker = BasicMapMarker.Cast( BasicMap().GetMarkerByVector(clickPos, radius) );
				//Print("[BASICMAP] OpenEditor " + clickPos);
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
				QueueListRefresh();
				return true;
			}
        }
		return super.OnDoubleClick(w, x, y, button);
    }
	
	
	void QueueListRefresh(){
		if ( m_CurrentListOffset > 0){
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater( this.StepIconsList, 50, false, -1);
		} else {
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater( this.PopulateMarkerList, 50, false);
		}
	}
	
	void UpdateMe(){
		if (BasicMap().ShowSelfOnMap()){
			string icon = GetSafeIconPath(m_MeMarker.GetIcon());
			m_Map.AddUserMark(m_MeMarker.GetPosition(), " ME", m_MeMarker.GetColour(), icon);
			m_PostionText.SetText("Postion: " + m_MeMarker.GetPosition().ToString(true));
		}
	}
	
	void ~BasicMapMenu()
    {
		// Cancel any pending UpdateMarkers callback before destruction
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.UpdateMarkers);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.UpdateContentAreaSize);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.PopulateMarkerList);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.StepIconsList);
		
		CloseRightClick();
		CloseEditor();
		UnLockControls();
		BasicMap().OnMapClose();
		delete m_MeMarker;
		if (layoutRoot) layoutRoot.Show(false);
    }
	
	bool IsOpen() {
		return m_PanelIsOpen;
	}

	void SetOpen(bool open) {
		if (!m_PanelIsOpen && open){
			layoutRoot.Show(true);
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateMarkers, 45, false);
		}
		if (m_PanelIsOpen && !open){
			CloseRightClick();
			CloseEditor();
			BasicMap().OnMapClose();
			delete m_MeMarker;
			layoutRoot.Show(false);
			UnLockControls();
		}
		m_PanelIsOpen = open;
	}
	
	//On click doesn't seem to work with map Widgets
	override bool OnMouseButtonDown(Widget w, int x, int y, int button ){
		//Print("[BASICMAP] OnMouseButtonDown " + w.GetName() + " X: " + x + " Y: " + y + " IsEditorOpen():" + IsEditorOpen() );
		vector clickPos;
		float radius;
		if (w == m_Map && button == MouseState.LEFT && !IsEditorOpen() && !IsRightClickMenuOpen()){
			clickPos = MapClickPosition(x,y);
			radius = (m_Map.GetScale() * 110) + 5;
			if (BasicMap().GetMarkerByVector(clickPos, radius)){
				m_SelectedMarker = BasicMapMarker.Cast(BasicMap().GetMarkerByVector(clickPos, radius));
				if (m_SelectedMarker){
					//Print("[BASICMAP]" + m_SelectedMarker.GetName() + " Marker Found at " + clickPos);
					OpenEditor(x, y);
					return true;
				}
			}
		}
		if ( w == m_Map &&  button == MouseState.RIGHT && !IsEditorOpen() && !IsRightClickMenuOpen()){
			clickPos = MapClickPosition(x,y);
			radius = (m_Map.GetScale() * 110) + 5;
			if (BasicMap().GetMarkerByVector(clickPos, radius)){
				m_SelectedMarker = BasicMapMarker.Cast(BasicMap().GetMarkerByVector(clickPos, radius));
				//Print("[BASICMAP]" + m_SelectedMarker.GetName() + " Marker Found at " + clickPos);
				if (m_SelectedMarker){
					OpenRightClick(x, y);
					return true;
				}
			}
		}
		if ( w && w.GetParent() && button == MouseState.LEFT && IsRightClickMenuOpen()){
			if (w.GetParent().GetName() != "RightClickPanel"){
				CloseRightClick();
			}
			return true;
		}
		return super.OnMouseButtonDown(w, x, y, button );
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{			
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
				// Remember this marker's color for the next new marker
				BasicMapMarkerFactory.RememberColor(m_SelectedMarker.Colour[0], m_SelectedMarker.Colour[1], m_SelectedMarker.Colour[2], m_SelectedMarker.Alpha, m_SelectedMarker.GetIcon());
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
	
	bool IsRightClickMenuOpen(){
		if (m_RightClickMenu){
			return m_RightClickMenu.IsOpen();
		}
		return false;
	}
	
	void RefreshMarkerList(){
		if (m_MarkerList){
			bool needsRebuild = false;
			for (int i = 0; i < m_MarkerList.Count(); i++){
				if (m_MarkerList.Get(i)){
					if (!m_MarkerList.Get(i).Refresh()){
						needsRebuild = true;
					}
				}
			}
			// Rebuild the entire list instead of removing by index.
			// Deferred RemoveOrdered by index is unsafe: after the first
			// removal shifts the array, subsequent queued indices are stale.
			if (needsRebuild){
				PopulateMarkerList();
			}
		}
	}
	
	
	override void LockControls() {
		GetGame().GetMission().GetHud().ShowHudUI( false );
		GetGame().GetMission().GetHud().ShowQuickbarUI( false );
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
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
						if (itemType.Contains("pen_") != -1){
                            return GetBasicMapConfig().AllowPlayerMarkers;
						}
                    }
                }
            }
			return false;
		} 
		return GetBasicMapConfig().AllowPlayerMarkers;
	}
	
	
	void CloseRightClick(){
		//Print("[BASICMAP] CloseRightClick()");
		if (m_RightClickMenu){
			m_RightClickMenu.Close();
		}
	}
	
	void OpenRightClick(int x, int y){
		//Print("[BASICMAP] OpenRightClick(int " + x + ", int " + y +")");
		if (!m_RightClickMenu){
			m_RightClickMenu = new BasicMapRightClick(m_Editor);
		}
		m_RightClickMenu.Open(m_SelectedMarker, x,y);
	}
}