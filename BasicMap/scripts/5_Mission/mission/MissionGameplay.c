modded class MissionGameplay extends MissionBase
{
	ref array<ref BasicMapHUDMarker> m_hudMarkers;
	
	override void OnMissionStart(){
		super.OnMissionStart();
		BasicMap();
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateHuDIcons, 5000, true);
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

        if (input.LocalPress("UABasicMap", false) && AllowedToOpenBasicMap()) {
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
	    m_BasicMapMenu = BasicMapMenu.Cast(GetUIManager().EnterScriptedMenu(BASICMAP_MENU, null));
		m_BasicMapMenu.LockControls();
	    m_BasicMapMenu.SetOpen(true);
		m_BasicMapMenu_Opening = false;
	}
	
	void BasicMapOpenPanel()
	{	
		GetGame().GetUIManager().ShowScriptedMenu(m_BasicMapMenu, NULL);
	    m_BasicMapMenu.SetOpen(true);
		m_BasicMapMenu.UpdateMarkers();
		m_BasicMapMenu.LockControls();
		m_BasicMapMenu_Opening = false;
	}
	
	void BasicMapClosePanel()
	{
		m_BasicMapMenu.CloseEditor();//Make sure if a marker was open that its closed and saved
		m_BasicMapMenu.SetOpen(false);
		m_BasicMapMenu.UnLockControls()
        GetGame().GetUIManager().HideScriptedMenu(m_BasicMapMenu);
		GetGame().GetUIManager().CloseMenu(BASICMAP_MENU);
		m_BasicMapMenu_Opening = false;
	}
	
	bool BasicMapHasPen(){
		
	}
	
	bool AllowedToOpenBasicMap(){
        if (GetBasicMapConfig() && GetBasicMapConfig().RequireMapItemInInventory) {
            DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());

            if (player){
				array<EntityAI> itemsArray = new array<EntityAI>;
				player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            	    
                for (int i = 0; i < itemsArray.Count(); i++){
                    if (itemsArray.Get(i) && itemsArray.Get(i).IsInherited(ItemMap)){
                            return true;
                    }
                }
            }
        } else if (GetBasicMapConfig().OnlyOnOpenAction){
			return false;
		} else {
			return true;
		}
        return false;
    }
}