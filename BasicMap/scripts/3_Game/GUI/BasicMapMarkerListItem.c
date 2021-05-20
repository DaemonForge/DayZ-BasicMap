class BasicMapMarkerListItem  extends ScriptedWidgetEventHandler {
	BasicMapMarker		m_Marker;
	BasicMapMenu		m_MapMenu;
	
	Widget				m_Root;
	
	Widget				m_Panel;
	
	ImageWidget			m_icon;
	TextWidget			m_name;
	
	ButtonWidget		m_Selector;
	
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
		m_Root.Show(false);
		m_Panel.Show(false);
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
			m_icon.LoadImageFile(0, m_Marker.GetIcon());
			m_icon.SetColor(m_Marker.GetColour());
			
			m_name.SetText(m_Marker.GetName());
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