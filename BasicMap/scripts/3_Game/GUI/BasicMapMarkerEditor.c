class BasicMapMarkerEditor  extends ScriptedWidgetEventHandler {
		
	protected BasicMapMarker		m_SelectedMarker;
	
	protected float						m_ScreenX;
	protected float						m_ScreenY;
	protected float						m_WidgetX;
	protected float						m_WidgetY;
	protected float						m_WidgetWidth;
	protected float						m_WidgetHeight;
	
	
	protected bool						m_EditorIsOpen = false;
	protected bool						m_NameFieldFocused = false;
	
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
		
		m_Editor_3DMaker 			= Widget.Cast(m_EditorRoot.FindAnyWidget( "ThreeDMarkerPanel" ));
		m_Editor_3DMakerBox 		= CheckBoxWidget.Cast(m_EditorRoot.FindAnyWidget( "ThreeDMarker" ));
	
		m_Editor_PartyMarker 		= Widget.Cast(m_EditorRoot.FindAnyWidget( "PartyMarkerPanel" ));
		m_Editor_PartyMarkerBox 	= CheckBoxWidget.Cast(m_EditorRoot.FindAnyWidget( "PartyMarker" ));
		
		m_Editor_Colour_Red 		= SliderWidget.Cast(m_EditorRoot.FindAnyWidget( "Red" ));
		m_Editor_Colour_Green 		= SliderWidget.Cast(m_EditorRoot.FindAnyWidget( "Green" ));
		m_Editor_Colour_Blue 		= SliderWidget.Cast(m_EditorRoot.FindAnyWidget( "Blue" ));
		m_Editor_Colour_Alpha 		= SliderWidget.Cast(m_EditorRoot.FindAnyWidget( "Alpha" ));
		
		m_EditorRoot.SetHandler(this);
		m_Editor_PartyMarker.Show(BasicMap().PARTY_KEY != "");
		m_EditorRoot.Show(false);
	}
	
	void ~BasicMapMarkerEditor(){
		if (m_EditorRoot){
			m_EditorRoot.Unlink();
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
	
	// Helper to update a color slider's visual feedback and the marker value
	// channel: 0=R, 1=G, 2=B, 3=Alpha
	protected void UpdateColorSlider(SliderWidget slider, int channel){
		int val = slider.GetCurrent();
		if (channel < 3){
			m_SelectedMarker.Colour[channel] = val;
		} else {
			m_SelectedMarker.Alpha = val;
		}
		
		if (val <= 0){
			int dimR = 0; int dimG = 0; int dimB = 0;
			if (channel == 0) dimR = 35;
			if (channel == 2) dimB = 35;
			if (channel == 3){ dimR = 55; dimG = 55; dimB = 55; }
			slider.SetColor(ARGB(200, dimR, dimG, dimB));
		} else {
			float barColour = val / 255.0;
			int baseRange = 205;
			int baseOffset = 120;
			if (channel == 3){
				baseRange = 150;
				baseOffset = 55;
			}
			barColour = barColour * baseRange;
			barColour = barColour + baseOffset;
			int safeVal = Math.Clamp(barColour, 120, 255);
			int cR = 0; int cG = 0; int cB = 0;
			if (channel == 0) cR = safeVal;
			if (channel == 1) cG = safeVal;
			if (channel == 2) cB = safeVal;
			if (channel == 3){ cR = safeVal; cG = safeVal; cB = safeVal; }
			int sliderAlpha = 200;
			slider.SetColor(ARGB(sliderAlpha, cR, cG, cB));
		}
		RefreshEditorIcon();
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (w == m_Editor_Colour_Red){
			UpdateColorSlider(m_Editor_Colour_Red, 0);
		}
		if (w == m_Editor_Colour_Green){
			UpdateColorSlider(m_Editor_Colour_Green, 1);
		}
		if (w == m_Editor_Colour_Blue){
			UpdateColorSlider(m_Editor_Colour_Blue, 2);
		}
		if (w == m_Editor_Colour_Alpha){
			UpdateColorSlider(m_Editor_Colour_Alpha, 3);
		}
		if (w == m_Editor_Name){
			m_SelectedMarker.SetName(m_Editor_Name.GetText());
			m_Editor_Name.SetText(m_Editor_Name.GetText());
		}
		if (w == m_Editor_3DMakerBox){
			m_SelectedMarker.ShowOnHUD(m_Editor_3DMakerBox.IsChecked());
		}
        return super.OnChange(w,x,y,finished);
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		if (w == m_Editor_Name)
		{
			m_NameFieldFocused = true;
		}
		return super.OnFocus(w, x, y);
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		if (w == m_Editor_Name)
		{
			m_NameFieldFocused = false;
		}
		return super.OnFocusLost(w, x, y);
	}
	
	bool IsNameFieldFocused()
	{
		return m_NameFieldFocused;
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
	
	void OpenEditor(int x, int y, BasicMapMarker marker){
		float ScreenWidth = 0;
		float ScreenHeight = 0;
		GetGame().GetWorkspace().GetScreenSize(ScreenWidth, ScreenHeight);
		m_ScreenX = ScreenWidth;
		m_ScreenY = ScreenHeight;
		m_Editor.GetSize(m_WidgetWidth, m_WidgetHeight);
		if (marker){
			m_SelectedMarker = BasicMapMarker.Cast(marker);
			m_EditorIsOpen = true;
			m_EditorRoot.Show(true);
			
			// NOTE: Do NOT call PlayerControlDisable here!
			// The BasicMapMenu already handles control locking for the entire map UI.
			// Adding another disable here causes unbalanced enable/disable calls.
			
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
			int green = m_SelectedMarker.Colour[1];
			int blue = m_SelectedMarker.Colour[2];
			int alpha = m_SelectedMarker.Alpha;
			
			m_Editor_Colour_Red.SetCurrent(red);
			m_Editor_Colour_Green.SetCurrent(green);
			m_Editor_Colour_Blue.SetCurrent(blue);
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
		m_NameFieldFocused = false;
		m_EditorIsOpen = false;
		m_EditorRoot.Show(false);
		m_Editor_Name.SetText("");
		m_Editor_Colour_Red.SetCurrent(150);
		m_Editor_Colour_Green.SetCurrent(150);
		m_Editor_Colour_Blue.SetCurrent(150);
		m_Editor_Colour_Alpha.SetCurrent(150);
		
		// NOTE: Do NOT call PlayerControlEnable here!
		// The BasicMapMenu handles all control locking/unlocking.
	}
	
	bool IsEditorOpen(){
		
		return m_EditorIsOpen && m_EditorRoot.IsVisible();
	}
}