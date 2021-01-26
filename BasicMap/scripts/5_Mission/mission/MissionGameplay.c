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
		int preventRunAway = 500; //Sure if you have more than 500 Makers this might become an issue but lets hope that this is so unlikely its not an issue
		while (m_hudMarkers.Count() > 0 && preventRunAway > 0){
			preventRunAway--;
			m_hudMarkers.Get(0).Show(false);
			m_hudMarkers.Get(0).OnDelete();
			m_hudMarkers.Remove(0);
		}
		m_hudMarkers.Clear(); //Just to make sure :)
		for (int j = 0; j < BasicMap().Count(); j++){
			m_hudMarkers.Insert(new ref BasicMapHUDMarker());
			m_hudMarkers.Get(j).Init(BasicMap().Marker(j));
		}
	}

	override void OnUpdate (float timeslice) {
        super.OnUpdate(timeslice);
		
        Input input = GetGame().GetInput();
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (input.LocalPress("UAUIBack", false) && player && !player.IsUnconscious()){
            if (m_BasicMapMenu != NULL && GetGame().GetUIManager().GetMenu() == m_BasicMapMenu) {
				if (m_BasicMapMenu.IsEditorOpen()){
					m_BasicMapMenu.CloseEditor();
				} else {
               	 	BasicMapClosePanel();
					m_BasicMapMenu_Opening = false;
				}
            }
        }
		if (player && player.IsUnconscious()){
			if (m_BasicMapMenu != NULL && GetGame().GetUIManager().GetMenu() == m_BasicMapMenu) {
				if (m_BasicMapMenu.IsEditorOpen()){
					m_BasicMapMenu.CloseEditor();
				}
               	BasicMapClosePanel();
				m_BasicMapMenu_Opening = false;
            }
		}

        if (input.LocalPress("UABasicMap", false) && player && !player.IsUnconscious()) {
			if (AllowedToOpenBasicMap()){
	            if (m_BasicMapMenu) {
	                if (m_BasicMapMenu.IsOpen() && !m_BasicMapMenu.IsEditorOpen() ) {
						BasicMapClosePanel();
	                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
						GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.BasicMapOpenPanel, 330, false);
						m_BasicMapMenu_Opening = true;
	                }
	            } else if (GetGame().GetUIManager().GetMenu() == NULL && m_BasicMapMenu == null) {
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.BasicMapCreatePanel, 330, false);
					m_BasicMapMenu_Opening = true;
	            }
			}
        }
		
		if (input.LocalPress("UABasicMap3DMarkers", false) && GetGame().GetUIManager().GetMenu() == NULL && player && !player.IsUnconscious()) {
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
		m_BasicMapMenu.UnLockControls();
        GetGame().GetUIManager().HideScriptedMenu(m_BasicMapMenu);
		GetGame().GetUIManager().CloseMenu(BASICMAP_MENU);
		m_BasicMapMenu_Opening = false;
	}
	
	bool BasicMapHasPen(){
		
	}
	
	bool AllowedToOpenBasicMap(){
		if (m_BasicMapMenu_Opening){
			return false;
		}
        if (GetBasicMapConfig() && GetBasicMapConfig().RequireMapItemInInventory) {
            DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());

            if (player){
				array<EntityAI> itemsArray = new array<EntityAI>;
				player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            	    
                for (int i = 0; i < itemsArray.Count(); i++){
                    if (itemsArray.Get(i) && itemsArray.Get(i).IsInherited(ItemMap)){
						ItemMap mapItem = ItemMap.Cast(itemsArray.Get(i));
						if (GetBasicMapConfig().SaveMarkersToMapItem && mapItem ) {
							mapItem.SyncMapMarkers();
							BasicMap().SetMapItem(mapItem);
						}
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