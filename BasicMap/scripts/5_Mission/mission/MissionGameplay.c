modded class MissionGameplay extends MissionBase
{
	ref array<ref BasicMapHUDMarker> m_hudMarkers;
	
	override void OnMissionStart(){
		super.OnMissionStart();
		BasicMap();
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateHuDIcons, 3000, true);
	}
	
	void UpdateHuDIcons(){
		if (!m_hudMarkers){
			m_hudMarkers = new ref array<ref BasicMapHUDMarker>;
		}
		for (int i = 0; i < m_hudMarkers.Count(); i++){
			m_hudMarkers.Get(i).Show(false);
		}
		m_hudMarkers.Clear();
		for (int j = 0; j < BasicMap().Count(); j++){
			m_hudMarkers.Insert(new ref BasicMapHUDMarker());
			m_hudMarkers.Get(j).Init(BasicMap().Marker(j));
		}
	}
	
	override void OnUpdate (float timeslice) {
        super.OnUpdate(timeslice);

        Input input = GetGame().GetInput();
        if (input.LocalPress("UAUIBack", false)) {
            if (m_BasicMapMenu != NULL && GetGame().GetUIManager().GetMenu() == m_BasicMapMenu) {
				if (m_BasicMapMenu.IsEditorOpen()){
					m_BasicMapMenu.CloseEditor();
				} else {
               	 	BasicMapClosePanel();
					m_BasicMapMenu_Opening = false;
				}
            }
        }

        if (input.LocalPress("UABasicMap", false)) {
            if (m_BasicMapMenu) {
                if (m_BasicMapMenu.IsOpen() && !m_BasicMapMenu.IsEditorOpen()) {
					BasicMapClosePanel();
                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
					BasicMapOpenPanel();
					m_BasicMapMenu_Opening = true;
                }
            } else if (GetGame().GetUIManager().GetMenu() == NULL && m_BasicMapMenu == null) {
				BasicMapCreatePanel();
				m_BasicMapMenu_Opening = true;
            }
        }
		
		 if (input.LocalPress("UABasicMap3DMarkers", false) && GetGame().GetUIManager().GetMenu() == NULL) {
            BasicMap().ToggleMarkersOnHUD();
        }
    }
	
	void BasicMapCreatePanel()
	{
		BasicMapLockControls();
	    m_BasicMapMenu = BasicMapMenu.Cast(GetUIManager().EnterScriptedMenu(BASICMAP_MENU, null));
	    BasicMapLockControls();
	    m_BasicMapMenu.SetOpen(true);
		m_BasicMapMenu_Opening = false;
	}
	
	void BasicMapOpenPanel()
	{	
		GetGame().GetUIManager().ShowScriptedMenu(m_BasicMapMenu, NULL);
	    m_BasicMapMenu.SetOpen(true);
		m_BasicMapMenu.UpdateMarkers();
	    BasicMapLockControls();
		m_BasicMapMenu_Opening = false;
	}
	
	void BasicMapClosePanel()
	{
		m_BasicMapMenu.CloseEditor();//Make sure if a marker was open that its closed and saved
		m_BasicMapMenu.SetOpen(false);
        GetGame().GetUIManager().HideScriptedMenu(m_BasicMapMenu);
		GetGame().GetUIManager().CloseMenu(BASICMAP_MENU);
		BasicMapUnLockControls();
		m_BasicMapMenu_Opening = false;
	}
	
	private void BasicMapLockControls() {
		GetGame().GetMission().GetHud().ShowHudUI( false );
		GetGame().GetMission().GetHud().ShowQuickbarUI( false );
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_MOUSE_ALL);
        GetGame().GetUIManager().ShowUICursor(true);
    }

    private void BasicMapUnLockControls() {
		GetGame().GetMission().GetHud().ShowHudUI( true );
		GetGame().GetMission().GetHud().ShowQuickbarUI( true );
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
    }
}