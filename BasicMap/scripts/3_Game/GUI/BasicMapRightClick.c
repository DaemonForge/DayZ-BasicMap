class BasicMapRightClick  extends ScriptedWidgetEventHandler {
	protected BasicMapMarker m_SelectedMarker;
	protected Widget		m_RightClickRoot;
	
	protected Widget		m_RightClickMenu;
	protected ButtonWidget	m_Delete;
	protected ButtonWidget	m_Change;
	
	protected Widget		m_GroupSelector;
	
	protected ButtonWidget	m_Next;
	protected ButtonWidget	m_Previous;
	protected TextWidget	m_GroupName
	
	void BasicMapRightClick(Widget parent, BasicMapMarker marker){
		m_RightClickRoot				= GetGame().GetWorkspace().CreateWidgets( "BasicMap/gui/layouts/RightClickMenu.layout", parent);
		m_RightClickMenu					= Widget.Cast(m_RightClickRoot.FindAnyWidget("RightClickMenu"));
		m_GroupSelector					= Widget.Cast(m_RightClickRoot.FindAnyWidget("GroupSelector"));
		
		m_RightClickRoot.Show(false);
		m_GroupSelector.Show(false);
	}
	
	
}