class BasicMapRightClick  extends ScriptedWidgetEventHandler {
	protected bool			m_IsOpen = false;
	
	protected BasicMapMarker m_SelectedMarker;
	protected Widget		m_RightClickRoot;
	
	protected Widget		m_RightClickMenu;
	protected ButtonWidget	m_Delete;
	protected ButtonWidget	m_Change;
	
	protected Widget		m_GroupSelector;
	
	protected ButtonWidget	m_Next;
	protected ButtonWidget	m_Previous;
	protected TextWidget	m_GroupName
	
	protected string		m_CurGroup = BasicMap().CLIENT_KEY;
	
	protected bool			m_GroupSelector_Opened = false;
	
	void BasicMapRightClick( Widget parent ){
		m_RightClickRoot				= Widget.Cast(GetGame().GetWorkspace().CreateWidgets( "BasicMap/gui/layouts/RightClickMenu.layout", parent));
		m_RightClickMenu				= Widget.Cast(m_RightClickRoot.FindAnyWidget("RightClickMenu"));
		m_GroupSelector					= Widget.Cast(m_RightClickRoot.FindAnyWidget("GroupSelector"));
		
		m_Delete						= ButtonWidget.Cast(m_RightClickRoot.FindAnyWidget("Delete"));
		m_Change						= ButtonWidget.Cast(m_RightClickRoot.FindAnyWidget("Change"));
		
		m_Previous						= ButtonWidget.Cast(m_RightClickRoot.FindAnyWidget("Previous"));
		m_Next							= ButtonWidget.Cast(m_RightClickRoot.FindAnyWidget("Next"));
		
		m_GroupName						= TextWidget.Cast(m_RightClickRoot.FindAnyWidget("GroupName"));
		
		m_RightClickRoot.SetHandler(this);
		
		m_GroupSelector.Show(false);
		m_RightClickRoot.Show(false);
		m_RightClickMenu.Show(false);
	}
	
	bool IsOpen(){
		
		return m_IsOpen && m_RightClickRoot.IsVisible();
	}
	
	void Open(BasicMapMarker marker, int x, int y ){
		m_IsOpen = true;
		m_SelectedMarker = BasicMapMarker.Cast(marker);
		m_RightClickRoot.SetPos(x,y);
		m_RightClickRoot.Show(true);
		m_RightClickMenu.Show(true);
		m_CurGroup = m_SelectedMarker.GetGroup();
	}

	void Close(){
		m_IsOpen = false;
		m_RightClickRoot.Show(false);
		m_RightClickMenu.Show(false);
		m_SelectedMarker = NULL;
	}
	
	void ~BasicMapRightClick(){
		m_GroupSelector.Show(false);
		m_RightClickRoot.Show(false);
		m_RightClickMenu.Show(false);
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		if (w == m_Delete){
			//Print("[BASICMAP] BasicMapRightClick OnClick() Delete");
			if (m_SelectedMarker){
				BasicMap().RemoveMarker(m_SelectedMarker);
			}
			if ( m_BasicMapMenu ){
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_BasicMapMenu.QueueListRefresh, 1, false);
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_BasicMapMenu.CloseRightClick, 200, false);
			}
			return true;
		}
		if (w == m_Change){
			ToggleSelector();
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
	
	void ToggleSelector(){
		m_GroupSelector_Opened = !m_GroupSelector_Opened;
		m_GroupSelector.Show(m_GroupSelector_Opened);		
	}
	
	
}