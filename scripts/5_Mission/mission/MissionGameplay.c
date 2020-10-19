modded class MissionGameplay extends MissionBase
{
	void MissionGameplay(){
		BasicMap();
	}
	
	override void OnUpdate (float timeslice) {
        super.OnUpdate(timeslice);

        Input input = GetGame().GetInput();
        if (input.LocalPress("UAUIBack", false)) {
            if (m_BasicMapMenu != NULL && GetGame().GetUIManager().GetMenu() == m_BasicMapMenu) {
                BasicMapClosePanel();
				m_BasicMapMenu_Opening = false;
            }
        }

        if (input.LocalPress("UABasicMap", false)) {
            if (m_BasicMapMenu) {
                if (m_BasicMapMenu.IsOpen()) {
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
		m_BasicMapMenu.SetOpen(false);
        GetGame().GetUIManager().HideScriptedMenu(m_BasicMapMenu);
		BasicMapUnLockControls();
		m_BasicMapMenu_Opening = false;
	}
	
	private void BasicMapLockControls() {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_MOUSE_ALL);
        GetGame().GetUIManager().ShowUICursor(true);
    }

    private void BasicMapUnLockControls() {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
    }
}