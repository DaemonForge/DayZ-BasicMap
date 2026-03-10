class BasicMapMarkerListItem  extends ScriptedWidgetEventHandler {
	BasicMapMarker		m_Marker;
	BasicMapMenu		m_MapMenu;
	
	Widget				m_Root;
	
	Widget				m_Panel;
	
	ImageWidget			m_icon;
	TextWidget			m_name;
	
	ButtonWidget		m_Selector;
	
	// Cache to avoid reloading icon/color every refresh
	protected string	m_LastIcon = "";
	protected int		m_LastColor = 0;
	protected string	m_LastName = "";
	
	void BasicMapMarkerListItem(Widget parent, BasicMapMenu mapMenu, BasicMapMarker marker){
		m_Marker 			= marker;
		m_MapMenu			= mapMenu;
		m_Root				= Widget.Cast(GetGame().GetWorkspace().CreateWidgets( "BasicMap/gui/layouts/MarkerListItem.layout", parent));
		
		m_Panel 			= Widget.Cast(m_Root.FindAnyWidget( "MarkerPanel" ));
		m_icon 				= ImageWidget.Cast(m_Root.FindAnyWidget( "MarkerIcon" ));
		m_name 				= TextWidget.Cast(m_Root.FindAnyWidget( "MarkerName" ));
		m_Selector 			= ButtonWidget.Cast(m_Root.FindAnyWidget( "Marker" ));
		
		Refresh();
		
		m_Root.SetHandler(this);
	}
	
	void ~BasicMapMarkerListItem(){
		if (m_Root){
			m_Root.Show(false);
			m_Root.Unlink();
		}
		if (m_Panel) m_Panel.Show(false);
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{		
		//Print("[BASICMAP] MarkerListItem OnClick");
		if (w == m_Selector) {
			m_MapMenu.SetMapPos( m_Marker.GetPosition() );
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
	
	override bool OnDoubleClick( Widget w, int x, int y, int button )
	{
	
		//Print("[BASICMAP] MarkerListItem OnDoubleClick");
		if (w == m_Selector && button == MouseState.LEFT && m_Marker.Editable()) {
			m_MapMenu.SetMapPos( m_Marker.GetPosition() );
			m_MapMenu.OpenEditorSelected(m_Marker);
			return true;
		}
		if (w == m_Selector && button == MouseState.RIGHT) { //Delete?
			return true;
		}
		return super.OnDoubleClick(w, x, y, button);
	
	}

	bool Refresh(){
		if (m_Marker){
			string curIcon = m_Marker.GetIcon();
			int curColor = m_Marker.GetColour();
			string curName = m_Marker.GetName();
			
			// Only update widgets when values actually changed
			if (curIcon != m_LastIcon){
				m_LastIcon = curIcon;
				m_icon.LoadImageFile(0, curIcon);
			}
			if (curColor != m_LastColor){
				m_LastColor = curColor;
				m_icon.SetColor(curColor);
			}
			if (curName != m_LastName){
				m_LastName = curName;
				m_name.SetText(curName);
			}
			return true;
		}
		Delete();
		return false;
	}
	
	void Delete(){
		m_Root.Show(false);
		m_Panel.Show(false);
	}
}