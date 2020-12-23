class ActionOpenBasicMap: ActionSingleUseBase
{
	
	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "Open Map";
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}
	
	override int GetActionCategory()
	{
		return AC_SINGLE_USE;
	}
	
	override void OnStartClient( ActionData action_data )
	{
		super.OnStartClient( action_data );
		ItemMap mapItem = ItemMap.Cast(action_data.m_MainItem);
		if ( mapItem )
		{
			if (GetBasicMapConfig().OnlyOnOpenAction && GetBasicMapConfig().SaveMarkersToMapItem){
				BasicMap().SetMapItem(mapItem);
			}
			if (m_BasicMapMenu) {
				if (GetGame().GetUIManager().GetMenu() == NULL) {
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.OpenPanel, 200, false);
				}
			} else if (GetGame().GetUIManager().GetMenu() == NULL && m_BasicMapMenu == NULL) {
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CreatePanel, 200, false);
			}
		}
		
	}
	
	override void OnStartServer( ActionData action_data )
	{
		super.OnStartServer(action_data );
		ItemMap mapItem = ItemMap.Cast(action_data.m_MainItem);
		if ( mapItem )
		{
			if (GetBasicMapConfig().SaveMarkersToMapItem){
				mapItem.SyncMapMarkers();
			}
		}
	}
	
	void OpenPanel(){
		GetGame().GetUIManager().ShowScriptedMenu(m_BasicMapMenu, NULL);
	    m_BasicMapMenu.SetOpen(true);
	    m_BasicMapMenu.LockControls();
	}
	
	void CreatePanel(){
	    m_BasicMapMenu = BasicMapMenu.Cast(GetGame().GetUIManager().EnterScriptedMenu(BASICMAP_MENU, null));
	    m_BasicMapMenu.SetOpen(true);
	    m_BasicMapMenu.LockControls();
	}
};
