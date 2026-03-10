// BasicMapNavigationHUD.c
// Handles the compass HUD (requires compass item) and GPS minimap (requires GPS item)
// GPS takes priority over compass - if both present, shows both

class BasicMapNavigationHUD extends Managed
{
	// Layout paths
	protected static const string COMPASS_LAYOUT_PATH = "BasicMap/gui/layouts/CompassHUD.layout";
	protected static const string MINIMAP_LAYOUT_PATH = "BasicMap/gui/layouts/MinimapHUD.layout";
	
	// Compass strip configuration
	protected static const float COMPASS_STRIP_WIDTH = 720.0;   // Width of one full 360 degree cycle
	protected static const float COMPASS_VIEW_WIDTH = 396.0;    // Visible width of compass strip
	protected static const float COMPASS_OFFSET_BASE = 720.0;   // Start offset (one full cycle to allow left scrolling)
	protected static const float MINIMAP_RADIUS = 400.0;        // 400m radius around player
	
	// Compass widgets
	protected Widget m_CompassRoot;
	protected Widget m_CompassContent;
	
	// Minimap widgets
	protected Widget m_MinimapRoot;
	protected MapWidget m_MinimapWidget;
	protected ImageWidget m_PlayerMarker;
	protected TextWidget m_CoordinatesText;
	protected bool m_PlayerMarkerDebugLogged = false;
	
	// State
	protected bool m_IsEnabled = false;
	protected bool m_HasCompass = false;
	protected bool m_HasGPS = false;
	protected bool m_HadCompass = false;     // Track previous frame state
	protected bool m_HadGPS = false;         // Track previous frame state
	protected float m_LastHeading = 0;
	
	void BasicMapNavigationHUD()
	{
	}
	
	void ~BasicMapNavigationHUD()
	{
		Destroy();
	}
	
	void Init()
	{
		// Create compass HUD
		m_CompassRoot = GetGame().GetWorkspace().CreateWidgets(COMPASS_LAYOUT_PATH);
		if (m_CompassRoot)
		{
			m_CompassContent = m_CompassRoot.FindAnyWidget("CompassContent");
			m_CompassRoot.Show(false);
		}
		
		// Create minimap HUD
		m_MinimapRoot = GetGame().GetWorkspace().CreateWidgets(MINIMAP_LAYOUT_PATH);
		if (m_MinimapRoot)
		{
			m_MinimapWidget = MapWidget.Cast(m_MinimapRoot.FindAnyWidget("MinimapWidget"));
			m_PlayerMarker = ImageWidget.Cast(m_MinimapRoot.FindAnyWidget("PlayerMarker"));
			m_CoordinatesText = TextWidget.Cast(m_MinimapRoot.FindAnyWidget("CoordinatesText"));
			
			if (m_PlayerMarker)
			{
				m_PlayerMarker.Show(true);
				m_PlayerMarker.SetSort(1000); // Force on top
				m_PlayerMarker.SetColor(ARGB(255, 255, 255, 255));
			}
			
			m_MinimapRoot.Show(false);
		}
	}
	
	void Destroy()
	{
		if (m_CompassRoot)
		{
			m_CompassRoot.Unlink();
			m_CompassRoot = null;
		}
		if (m_MinimapRoot)
		{
			m_MinimapRoot.Unlink();
			m_MinimapRoot = null;
		}
	}
	
	void Toggle()
	{
		m_IsEnabled = !m_IsEnabled;
		UpdateVisibility();
		
		if (m_IsEnabled)
		{
			Print("[BasicMap] Navigation HUD enabled");
		}
		else
		{
			Print("[BasicMap] Navigation HUD disabled");
		}
	}
	
	bool IsEnabled()
	{
		return m_IsEnabled;
	}
	
	void SetEnabled(bool enabled)
	{
		m_IsEnabled = enabled;
		UpdateVisibility();
	}
	
	void Update(float timeslice)
	{
		if (!m_IsEnabled)
		{
			return;
		}
		
		// Hide when any menu is open
		if (GetGame().GetUIManager().GetMenu() != NULL)
		{
			if (m_CompassRoot) m_CompassRoot.Show(false);
			if (m_MinimapRoot) m_MinimapRoot.Show(false);
			return;
		}
		
		Man player = GetGame().GetPlayer();
		if (!player)
		{
			if (m_CompassRoot) m_CompassRoot.Show(false);
			if (m_MinimapRoot) m_MinimapRoot.Show(false);
			return;
		}
		
		// Store previous state before checking
		m_HadCompass = m_HasCompass;
		m_HadGPS = m_HasGPS;
		
		// Check for navigation items in player inventory
		CheckNavigationItems(player);
		
		// Auto-disable if player lost all navigation items
		if (!m_HasCompass && !m_HasGPS)
		{
			// Only notify if we previously had at least one item
			if (m_HadCompass || m_HadGPS)
			{
				Print("[BasicMap] Navigation HUD auto-disabled - no navigation items");
			}
			
			// Reset enabled state and hide everything
			m_IsEnabled = false;
			if (m_CompassRoot) m_CompassRoot.Show(false);
			if (m_MinimapRoot) m_MinimapRoot.Show(false);
			return;
		}
		
		// Notify if compass was lost (but still have GPS)
		if (m_HadCompass && !m_HasCompass && m_HasGPS)
		{
			Print("[BasicMap] Compass lost - hiding compass HUD");
		}
		
		// Notify if GPS was lost (but still have compass)
		if (m_HadGPS && !m_HasGPS && m_HasCompass)
		{
			Print("[BasicMap] GPS lost - hiding minimap HUD");
		}
		
		// Update compass if player has one
		if (m_CompassRoot)
		{
			m_CompassRoot.Show(m_HasCompass);
			if (m_HasCompass) UpdateCompass(player);
		}
		
		// Update minimap if player has GPS
		if (m_MinimapRoot)
		{
			m_MinimapRoot.Show(m_HasGPS);
			if (m_HasGPS) UpdateMinimap(player);
		}
	}
	
	protected void CheckNavigationItems(Man player)
	{
		m_HasCompass = BasicMap().HasCachedCompass();
		m_HasGPS = BasicMap().HasCachedGPS();
	}
	
	protected void UpdateCompass(Man player)
	{
		if (!m_CompassContent)
		{
			return;
		}
		
		// Get player's heading (yaw from camera direction)
		// DayZ coordinates: X = East/West, Z = North/South (positive Z = North)
		// Atan2(x, z) gives: N=0deg, E=90deg, S=180deg/-180deg, W=-90deg
		vector camDir = GetGame().GetCurrentCameraDirection();
		float heading = Math.Atan2(camDir[0], camDir[2]) * Math.RAD2DEG;
		
		// Normalize to 0-360
		if (heading < 0)
		{
			heading = heading + 360;
		}
		
		m_LastHeading = heading;
		
		// Get actual view width from parent widget (CompassStrip)
		Widget compassStrip = m_CompassContent.GetParent();
		float viewWidth = COMPASS_VIEW_WIDTH;  // fallback
		float viewHeight = 38;
		if (compassStrip)
		{
			compassStrip.GetScreenSize(viewWidth, viewHeight);
		}
		float viewHalfWidth = viewWidth / 2.0;
		
		// Get actual content width to calculate pixels per degree
		float contentWidth = 2160;  // fallback - 3 full cycles at 720px each
		float contentHeight = 38;
		m_CompassContent.GetScreenSize(contentWidth, contentHeight);
		
		// Calculate scale factor - if content is rendered at different size than layout
		float scaleFactor = contentWidth / 2160.0;
		
		// Compass strip layout (2 pixels per degree at 1x scale):
		// - N at 0px, 720px, 1440px
		// - Each degree = 2 pixels
		// - Each mark widget is 30px wide, with text centered within
		// Scale all values by scaleFactor for actual screen size
		float pixelsPerDegree = 2.0 * scaleFactor;
		float markHalfWidth = 15.0 * scaleFactor;  // Half of 30px mark width for centering
		
		// Choose which cycle to use based on heading to keep view within valid content:
		// - Cycle 1 (base 0): Use for headings 180-360 (S through W to N)
		// - Cycle 2 (base 720): Use for headings 0-180 (N through E to S)
		// Both cycles show the same marks at the same visual positions, just different copies.
		float cycleOffset;
		if (heading < 180.0)
		{
			cycleOffset = 720.0 * scaleFactor;  // Cycle 2
		}
		else
		{
			cycleOffset = 0.0;  // Cycle 1
		}
		
		// Calculate mark position
		// Add markHalfWidth because layout positions are left-edge, but we want text center
		float markPosition = cycleOffset + (heading * pixelsPerDegree) + markHalfWidth;
		
		// Calculate strip X position to center the mark in view
		float stripX = viewHalfWidth - markPosition;
		
		m_CompassContent.SetPos(stripX, 0);
	}
	
	protected void UpdateMinimap(Man player)
	{
		if (!m_MinimapWidget)
		{
			return;
		}
		
		vector playerPos = player.GetPosition();
		
		// Center map on player position - pass world position directly
		// MapWidget.SetMapPos expects the world position vector
		m_MinimapWidget.SetMapPos(playerPos);
		
		// Set scale to show approximately 400m radius
		// Scale is a zoom factor - lower = more zoomed out, higher = more zoomed in
		// We want roughly 800m diameter visible in the 192px widget
		// A scale of around 0.1 to 0.15 gives a good minimap view
		m_MinimapWidget.SetScale(0.12);
		
		// Rotate player marker arrow to face player's look direction
		if (m_PlayerMarker)
		{
			vector camDir = GetGame().GetCurrentCameraDirection();
			float heading = Math.Atan2(camDir[0], camDir[2]) * Math.RAD2DEG;
			
			// SetRotation uses (yaw, pitch, roll) - we want to rotate around Z axis (roll)
			// Heading from Atan2(x,z) is already clockwise from North (0), which matches UI rotation
			m_PlayerMarker.SetRotation(0, 0, heading);
			if (!m_PlayerMarkerDebugLogged)
			{
				bool vis = m_PlayerMarker.IsVisibleHierarchy();
				float px, py; m_PlayerMarker.GetPos(px, py);
				float sx, sy; m_PlayerMarker.GetSize(sx, sy);
				Print(string.Format("[BasicMap][NavHUD] PlayerMarker debug: visible=%1 pos=(%2,%3) size=(%4,%5) heading=%6", vis, px, py, sx, sy, heading));
				m_PlayerMarkerDebugLogged = true;
			}
		}
		
		// Update coordinates text
		if (m_CoordinatesText)
		{
			int gridX = Math.Round(playerPos[0]);
			int gridZ = Math.Round(playerPos[2]);
			
			string coordStr = gridX.ToString() + " / " + gridZ.ToString();
			m_CoordinatesText.SetText(coordStr);
		}
	}
	
	protected void UpdateVisibility()
	{
		if (!m_IsEnabled)
		{
			if (m_CompassRoot) m_CompassRoot.Show(false);
			if (m_MinimapRoot) m_MinimapRoot.Show(false);
		}
		// Actual visibility depends on having the required items, handled in Update()
	}
	
	bool HasCompass()
	{
		return m_HasCompass;
	}
	
	bool HasGPS()
	{
		return m_HasGPS;
	}
	
	float GetCurrentHeading()
	{
		return m_LastHeading;
	}
}
