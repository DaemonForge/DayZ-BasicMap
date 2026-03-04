modded class MissionGameplay extends MissionBase
{
	autoptr array<autoptr BasicMapHUDMarker> m_hudMarkers;
	
	// Navigation HUD (compass and minimap)
	protected ref BasicMapNavigationHUD m_NavigationHUD;
	
	// Marker visibility key hold detection
	protected float m_MarkerKeyHoldTime = 0;           // How long K has been held
	protected bool m_MarkerKeyWasPressed = false;       // Track if key was pressed last frame
	protected float m_MarkerHoldCooldown = 0;           // Cooldown after hold action
	protected const float MARKER_HOLD_THRESHOLD = 2.5;  // 2.5 seconds to trigger hold action
	protected const float MARKER_HOLD_COOLDOWN = 3.5;   // 3.5 seconds before hold can trigger again
	
	override void OnMissionStart(){
		super.OnMissionStart();
		Print("BasicMap().Init();");
		BasicMap().Init();
		
		// Initialize navigation HUD
		m_NavigationHUD = new BasicMapNavigationHUD();
		m_NavigationHUD.Init();
		
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateHuDIcons, 2000, false);
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdateHuDIcons, 9000, true);
	}
	
	override void OnMissionFinish(){
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.UpdateHuDIcons);
		int preventRunAway = 500; //Sure if you have more than 500 Makers this might become an issue but lets hope that this is so unlikely its not an issue
		/*while (m_hudMarkers.Count() > 0 && preventRunAway > 0){
			preventRunAway--;
			m_hudMarkers.Get(0).Show(false);
			m_hudMarkers.Get(0).OnDelete();
			delete m_hudMarkers.Get(0);
			m_hudMarkers.Remove(0);
		}*/
		if (m_hudMarkers){
			m_hudMarkers.Clear(); //Just to make sure :)
			delete m_hudMarkers;
		}
		
		// Clean up navigation HUD
		if (m_NavigationHUD){
			m_NavigationHUD.Destroy();
			delete m_NavigationHUD;
		}
		
		super.OnMissionFinish();
	}
	
	
	void UpdateHuDIcons(){
		if (!m_hudMarkers){
			m_hudMarkers = new array<autoptr BasicMapHUDMarker>;
		}
		
		int markerCount = BasicMap().Count();
		int hudCount = m_hudMarkers.Count();
		
		// Rebuild if marker count changed OR markers were replaced (dirty flag).
		// SetMarkers/RemoveAllMarkers can replace all markers with the same count,
		// leaving HUD markers with dangling weak references to deleted objects.
		if (hudCount != markerCount || BasicMap().m_MarkersDirty){
			BasicMap().m_MarkersDirty = false;
			// Clear and rebuild
			m_hudMarkers.Clear();
			for (int j = 0; j < markerCount; j++){
				m_hudMarkers.Insert(new BasicMapHUDMarker());
				m_hudMarkers.Get(j).Init(BasicMap().Marker(j));
			}
		}
		// Otherwise, the existing HUD markers will update themselves via their CallLater
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
						GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.BasicMapOpenPanel, 2, false);
						m_BasicMapMenu_Opening = true;
	                }
	            } else if (GetGame().GetUIManager().GetMenu() == NULL && m_BasicMapMenu == null) {
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.BasicMapCreatePanel, 2, false);
					m_BasicMapMenu_Opening = true;
	            }
			}
        }
		
		// Handle marker visibility key (K) with short press cycle and long press quick toggle
		HandleMarkerVisibilityKey(input, player, timeslice);
		
		// Handle navigation HUD toggle (B key) and update
		HandleNavigationHUD(input, player, timeslice);
    }
	
	void BasicMapCreatePanel()
	{
	    m_BasicMapMenu = BasicMapMenu.Cast(GetUIManager().EnterScriptedMenu(BASICMAP_MENU, null));
		if (!m_BasicMapMenu){
			m_BasicMapMenu_Opening = false;
			return;
		}
		m_BasicMapMenu.LockControls();
	    m_BasicMapMenu.SetOpen(true);
		m_BasicMapMenu_Opening = false;
	}
	
	void BasicMapOpenPanel()
	{	
		if (!m_BasicMapMenu){
			m_BasicMapMenu_Opening = false;
			return;
		}
		GetGame().GetUIManager().ShowScriptedMenu(m_BasicMapMenu, NULL);
	    m_BasicMapMenu.SetOpen(true);
		m_BasicMapMenu.UpdateMarkers();
		m_BasicMapMenu.LockControls();
		m_BasicMapMenu_Opening = false;
	}
	
	void BasicMapClosePanel()
	{
		if (!m_BasicMapMenu){
			m_BasicMapMenu_Opening = false;
			return;
		}
		m_BasicMapMenu.CloseEditor();//Make sure if a marker was open that its closed and saved
		m_BasicMapMenu.SetOpen(false);
		m_BasicMapMenu.UnLockControls();
        GetGame().GetUIManager().HideScriptedMenu(m_BasicMapMenu);
		GetGame().GetUIManager().CloseMenu(BASICMAP_MENU);
		m_BasicMapMenu_Opening = false;
	}
	
	bool BasicMapHasPen(){
		if (!GetBasicMapConfig().RequirePenToMark){
			return true;
		}
		
		DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());
		if (!player){
			return false;
		}
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++){
			if (itemsArray.Get(i)){
				string itemType = itemsArray.Get(i).GetType();
				itemType.ToLower();
				if (itemType.Contains("pen_") != -1){
					return true;
				}
			}
		}
		return false;
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
	
	// Handle marker visibility key (K) with:
	// - Short press: Cycle through modes (Show All -> Server Only -> Local Only -> Hide All)
	// - Long press (2.5s): Toggle between Show All and Hide All
	// - 3.5s cooldown after hold before hold can trigger again
	void HandleMarkerVisibilityKey(Input input, PlayerBase player, float timeslice)
	{
		// Decrease cooldown timer
		if (m_MarkerHoldCooldown > 0){
			m_MarkerHoldCooldown = m_MarkerHoldCooldown - timeslice;
		}
		
		// Only process when no menu is open and player is valid
		if (GetGame().GetUIManager().GetMenu() != NULL || !player || player.IsUnconscious()){
			m_MarkerKeyHoldTime = 0;
			m_MarkerKeyWasPressed = false;
			return;
		}
		
		// Check if key is currently held
		float keyValue = input.LocalValue("UABasicMap3DMarkers", false);
		bool keyHeld = keyValue > 0;
		
		if (keyHeld){
			// Key is being held
			m_MarkerKeyHoldTime = m_MarkerKeyHoldTime + timeslice;
			
			// Check for long press threshold (only if not on cooldown)
			if (m_MarkerKeyHoldTime >= MARKER_HOLD_THRESHOLD && m_MarkerHoldCooldown <= 0){
				// Long press detected - quick toggle
				BasicMap().QuickToggleVisibility();
				Print("[BasicMap] Hold detected - Quick toggle to: " + BasicMap().GetVisibilityModeName());
				
				// Start cooldown and reset hold time to prevent re-triggering
				m_MarkerHoldCooldown = MARKER_HOLD_COOLDOWN;
				m_MarkerKeyHoldTime = 0; // Reset so we don't keep triggering
				m_MarkerKeyWasPressed = true; // Mark as processed
			}
			
			m_MarkerKeyWasPressed = true;
		}
		else {
			// Key was released
			if (m_MarkerKeyWasPressed){
				// Only do short press cycle if we didn't trigger a hold action
				// and hold time was less than threshold
				if (m_MarkerKeyHoldTime > 0 && m_MarkerKeyHoldTime < MARKER_HOLD_THRESHOLD){
					// Short press - cycle to next mode
					BasicMap().CycleVisibilityMode();
					Print("[BasicMap] Short press - Cycled to: " + BasicMap().GetVisibilityModeName());
				}
			}
			
			// Reset state
			m_MarkerKeyHoldTime = 0;
			m_MarkerKeyWasPressed = false;
		}
	}
	
	// Handle navigation HUD (B key to toggle, updates each frame when enabled)
	// Compass HUD shows when player has compass item
	// GPS minimap shows when player has working GPS (takes priority)
	void HandleNavigationHUD(Input input, PlayerBase player, float timeslice)
	{
		// Toggle navigation HUD with B key
		if (input.LocalPress("UABasicMapNavigation", false) && player && !player.IsUnconscious())
		{
			// Only toggle if no menu is open
			if (GetGame().GetUIManager().GetMenu() == NULL)
			{
				if (m_NavigationHUD)
				{
					m_NavigationHUD.Toggle();
				}
			}
		}
		
		// Update navigation HUD each frame
		if (m_NavigationHUD)
		{
			m_NavigationHUD.Update(timeslice);
		}
	}
}
