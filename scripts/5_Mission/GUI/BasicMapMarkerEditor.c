class BasicMapMarkerEditor  extends ScriptedWidgetEventHandler {
		
	protected float						m_ScreenX;
	protected float						m_ScreenY;
	protected float						m_WidgetX;
	protected float						m_WidgetY;
	protected float						m_WidgetWidth;
	protected float						m_WidgetHeight;
	
	
	protected bool						m_EditorIsOpen = false;
	
	protected Widget					m_EditorRoot;
	
	protected Widget					m_Editor;
	
	protected EditBoxWidget				m_Editor_Name;
	
	protected ButtonWidget				m_Editor_Close;
	
	protected ImageWidget				m_Editor_Icon;
	protected ButtonWidget				m_Editor_IconRight;
	protected ButtonWidget				m_Editor_IconLeft;
	protected int						m_Editor_CurIcon = 0;	
	
	protected Widget					m_Editor_3DMaker;
	protected CheckBoxWidget			m_Editor_3DMakerBox;
	
	protected Widget					m_Editor_PartyMarker;
	protected CheckBoxWidget			m_Editor_PartyMarkerBox;
		
	protected SliderWidget				m_Editor_Colour_Red;
	protected SliderWidget				m_Editor_Colour_Green;
	protected SliderWidget				m_Editor_Colour_Blue;
	protected SliderWidget				m_Editor_Colour_Alpha;
	
	
	void BasicMapMarkerEditor(Widget parent){
		
		m_EditorRoot				= GetGame().GetWorkspace().CreateWidgets( "BasicMap/gui/layouts/EditIcons.layout", parent);
				
		m_Editor 					= Widget.Cast(m_EditorRoot.FindAnyWidget( "Editor" ));
		
		m_Editor_Name 				=  EditBoxWidget.Cast(m_EditorRoot.FindAnyWidget( "Name" ));
	
		m_Editor_Close 				= ButtonWidget.Cast(m_EditorRoot.FindAnyWidget( "Close" ));
	
		m_Editor_Icon 				= ImageWidget.Cast(m_EditorRoot.FindAnyWidget( "Icon" ));
		m_Editor_IconRight 			= ButtonWidget.Cast(m_EditorRoot.FindAnyWidget( "Right" ));
		m_Editor_IconLeft 			= ButtonWidget.Cast(m_EditorRoot.FindAnyWidget( "Left" ));
		
		m_Editor_3DMaker = Widget.Cast(m_EditorRoot.FindAnyWidget( "ThreeDMarkerPanel" ));
		m_Editor_3DMakerBox = CheckBoxWidget.Cast(m_EditorRoot.FindAnyWidget( "ThreeDMarker" ));
	
		m_Editor_PartyMarker = Widget.Cast(m_EditorRoot.FindAnyWidget( "PartyMarkerPanel" ));
		m_Editor_PartyMarkerBox = CheckBoxWidget.Cast(m_EditorRoot.FindAnyWidget( "PartyMarker" ));
		
		m_Editor_Colour_Red = SliderWidget.Cast(m_EditorRoot.FindAnyWidget( "Red" ));
		m_Editor_Colour_Green = SliderWidget.Cast(m_EditorRoot.FindAnyWidget( "Green" ));
		m_Editor_Colour_Blue = SliderWidget.Cast(m_EditorRoot.FindAnyWidget( "Blue" ));
		m_Editor_Colour_Alpha = SliderWidget.Cast(m_EditorRoot.FindAnyWidget( "Alpha" ));
		
		m_EditorRoot.SetHandler(this);
		if (BasicMap().PARTY_KEY != ""){
			m_Editor_PartyMarker.Show(true);
		} else {
			m_Editor_PartyMarker.Show(false);
		}
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{		
		if (w == m_Editor_Close){
			CloseEditor();
			return true;
		}
		if (w == m_Editor_IconRight){
			StepIcon(1);
		}
		if (w == m_Editor_IconLeft){
			StepIcon(-1);
		}
		return super.OnClick(w, x, y, button);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		float barColour = 255;
		int safeBarColour = 255;
		if (w == m_Editor_Colour_Red){
			m_SelectedMarker.Colour[0] = m_Editor_Colour_Red.GetCurrent();
			if (m_Editor_Colour_Red.GetCurrent() <= 0){
				m_Editor_Colour_Red.SetColor(ARGB(255, 35, 0, 0));
			} else {
				barColour =  m_Editor_Colour_Red.GetCurrent() / 255;
				barColour = barColour * 205;
				barColour = barColour + 50; // So people can still tell which color each bar should of been
				safeBarColour = barColour; 
				m_Editor_Colour_Red.SetColor(ARGB(255,safeBarColour, 0, 0));
			}
			RefreshEditorIcon();
		}
		if (w ==  m_Editor_Colour_Green){
			m_SelectedMarker.Colour[1] = m_Editor_Colour_Green.GetCurrent();
			if (m_Editor_Colour_Green.GetCurrent() <= 0){
				m_Editor_Colour_Green.SetColor(ARGB(255, 35, 0, 0));
			} else {
				barColour =  m_Editor_Colour_Green.GetCurrent() / 255;
				barColour = barColour * 205;
				barColour = barColour + 50; // So people can still tell which color each bar should of been
				safeBarColour = barColour; 
				m_Editor_Colour_Green.SetColor(ARGB(255, 0, safeBarColour, 0));
			}
			RefreshEditorIcon();
		}
		if (w == m_Editor_Colour_Blue){
			m_SelectedMarker.Colour[2] = m_Editor_Colour_Blue.GetCurrent();
			if (m_Editor_Colour_Blue.GetCurrent() <= 0){
				m_Editor_Colour_Blue.SetColor(ARGB(255, 0, 0, 35));
			} else {
				barColour =  m_Editor_Colour_Blue.GetCurrent() / 255;
				barColour = barColour * 205;
				barColour = barColour + 50; // So people can still tell which color each bar should of been
				safeBarColour = barColour; 
				m_Editor_Colour_Blue.SetColor(ARGB(255, 0, 0, safeBarColour));
			}
			RefreshEditorIcon();
		}
		if (w == m_Editor_Colour_Alpha){
			m_SelectedMarker.Alpha = m_Editor_Colour_Alpha.GetCurrent();
			if (m_Editor_Colour_Alpha.GetCurrent() <= 0){
				m_Editor_Colour_Alpha.SetColor(ARGB(255, 55, 55, 55));
			} else {
				barColour =  m_Editor_Colour_Alpha.GetCurrent() / 255;
				barColour = barColour * 150;
				barColour = barColour + 55; // So people can still tell which color each bar should of been
				safeBarColour = barColour; 
				m_Editor_Colour_Alpha.SetColor(ARGB(210, safeBarColour, safeBarColour, safeBarColour));
			}
			RefreshEditorIcon();
		}
		if (w == m_Editor_Name){
			m_SelectedMarker.Name = m_Editor_Name.GetText();
			m_Editor_Name.SetText(m_SelectedMarker.GetName());
		}
		if (w == m_Editor_3DMakerBox){
			m_SelectedMarker.ShowOnHUD(m_Editor_3DMakerBox.IsChecked());
		}
        return super.OnChange(w,x,y,finished);
	}
	
	void StepIcon(int dir){
		m_Editor_CurIcon = m_Editor_CurIcon + dir;
		if (m_Editor_CurIcon < 0){
			m_Editor_CurIcon = GetBasicMapConfig().Icons.Count() - 1;
		} else if (m_Editor_CurIcon >= GetBasicMapConfig().Icons.Count() ){
			m_Editor_CurIcon = 0;
		}
		m_Editor_Icon.LoadImageFile(0,  GetBasicMapConfig().Icons.Get(m_Editor_CurIcon));
		m_SelectedMarker.SetIcon(GetBasicMapConfig().Icons.Get(m_Editor_CurIcon));
	}
	
	void RefreshEditorIcon(){
		m_Editor_Icon.SetColor(m_SelectedMarker.GetColour());
	}
	
	void OpenEditor(int x, int y){
		float ScreenWidth = 0;
		float ScreenHeight = 0;
		GetGame().GetWorkspace().GetScreenSize(ScreenWidth, ScreenHeight);
		m_ScreenX = ScreenWidth;
		m_ScreenY = ScreenHeight;
		m_Editor.GetSize(m_WidgetWidth, m_WidgetHeight);
		if (m_SelectedMarker){
			//Print("Editor Panel Called at X: " + x + " Y: " + y);
			m_EditorIsOpen = true;
			m_EditorRoot.Show(true);
			m_WidgetX  = x;
			m_WidgetY  = y;
			float maxX = m_ScreenX - m_WidgetWidth - 3;
			float maxY = m_ScreenY - m_WidgetHeight;
			if (m_WidgetX > maxX){
				m_WidgetX = m_WidgetX - m_WidgetWidth - 10;
			}
			
			if (m_WidgetY > maxY){
				m_WidgetY = m_WidgetY - m_WidgetHeight - 24;
			}
			
			m_EditorRoot.SetPos(m_WidgetX, m_WidgetY);
			//Print("Editor Panel Opened at X: " + m_WidgetX + " Y: " + m_WidgetY);
			
			int red = m_SelectedMarker.Colour[0];
			int blue = m_SelectedMarker.Colour[1];
			int green = m_SelectedMarker.Colour[2];
			int alpha = m_SelectedMarker.Alpha;
			
			m_Editor_Colour_Red.SetCurrent(red);
			m_Editor_Colour_Green.SetCurrent(blue);
			m_Editor_Colour_Blue.SetCurrent(green);
			m_Editor_Colour_Alpha.SetCurrent(alpha);
			
			m_Editor_Icon.LoadImageFile(0, m_SelectedMarker.Icon);
			
			m_Editor_CurIcon = GetBasicMapConfig().Icons.Find(m_SelectedMarker.Icon);
			
			m_Editor_Name.SetText(m_SelectedMarker.GetName());
			m_Editor_3DMakerBox.SetChecked(m_SelectedMarker.OnHUD());
			RefreshEditorIcon();
		} else {
			CloseEditor();
		}
	}	
	
	void CloseEditor(){
		m_EditorIsOpen = false;
		m_EditorRoot.Show(false);
		m_Editor_Name.SetText("");
		m_Editor_Colour_Red.SetCurrent(150);
		m_Editor_Colour_Green.SetCurrent(150);
		m_Editor_Colour_Blue.SetCurrent(150);
		m_Editor_Colour_Alpha.SetCurrent(150);
	}
	
	bool IsEditorOpen(){
		return m_EditorIsOpen;
	}
}