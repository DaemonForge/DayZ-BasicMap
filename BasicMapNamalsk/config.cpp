class CfgPatches
{
	class BasicMapNamalsk
	{
		requiredVersion = 0.1;
		requiredAddons[] = {
			"ns_dayz_gear_navigation",
			"namalsk_terrain",
			"BasicMap"
		};
	};
};

class CfgMods
{
	class BasicMapNamalsk
	{
		dir="BasicMapNamalsk";
        name="BasicMap";
        type="mod";
	    dependencies[]={"World"};
	    class defs
	    {
			class worldScriptModule
            {
                value="";
                files[]={ 
					"BasicMapNamalsk/scripts/4_World"
				};
            };
        };
    };
};

class CfgWorlds
{
	class Names;
	class CAWorld;
	class namalsk: CAWorld 
	{
		class Names
		{
			class Settlement_Vorkuta
			{
				name = "VORKUTA";
			};
			class Settlement_Jalovisko
			{
				name = "JALOVISKO";
			};
			class Settlement_Lubjansk
			{
				name = "LUBJANSK";
			};
			class Settlement_Nemsk
			{
				name = "NEMSK";
			};
			class Settlement_Norinsk
			{
				name = "NORINSK";
			};
			class Settlement_Brensk
			{
				name = "BRENSK";
			};
			class Settlement_TaraHarbor
			{
				name = "TARA HARBOR";
				type = "Village";
			};
			class Settlement_Sebjan
			{
				name = "SEBJAN";
			};
			class Area_Alakit
			{
				name = "ALAKIT";
			};
			class Area_NorinskPass
			{
				name = "Norinsk Pass";
				type = "Local";
			};
			class Area_SebjanWarehouses
			{
				name = "Warehouses";
				type = "Local";
			};
			class Area_Sibirsky2119
			{
				name = "Sibirskiy-2119";
				type = "Local";
			};
			class Area_SKAT12
			{
				name = "SKAT-12";
				type = "MilitaryOutpost";
			};
			class Area_TFBase
			{
				name = "TF Bering Outpost";
				type = "MilitaryOutpost";
			};
			class Area_BKT12
			{
				name = "BK-T12";
				type = "MilitaryOutpost";
			};
			class Area_BKT08
			{
				name = "BK-T08";
				type = "MilitaryOutpost";
			};
			class Area_BKT07
			{
				name = "BK-T07";
				type = "MilitaryOutpost";
			};
			class Area_BKM06
			{
				name = "BK-M06";
				type = "MilitaryOutpost";
			};
			class Area_BKL16
			{
				name = "BK-L16";
				type = "MilitaryOutpost";
			};
			class Area_BKL01
			{
				name = "BK-L01";
				type = "MilitaryOutpost";
			};
			class Area_ARI
			{
				name = "ATHENA Research Institute";
				type = "MilitaryOutpost";
			};
			class Area_A1
			{
				name = "ATHENA-1";
				type = "MilitaryOutpost";
			};
			class Area_A2
			{
				name = "ATHENA-2";
				type = "MilitaryOutpost";
			};
			class Area_BKL02
			{
				type = "MilitaryOutpost";
			};
			class Area_Sebval
			{
				name = "Sebjan Valley";
			};
			class Area_SebDam
			{
				name = "Sebjan Dam";
			};
			class Area_SebUran
			{
				name = "Sebjan Uranium mine";
			};
			class Area_RF1
			{
				name = "Refugee camp";
				type = "MilitaryOutpost";
			};
			class Area_RF2
			{
				name = "Refugee camp";
				type = "MilitaryOutpost";
			};
			class Area_Mohawk
			{
				name = "C-130J Mohawk";
				type = "MilitaryOutpost";
			};
			class Area_Airfield
			{
				name = "Sebjan Airfield";
				type = "Local";
			};
			class Area_ChemFac
			{
				name = "Factory";
				type = "IndustrialSite";
			};
			class Area_SebFac
			{
				name = "Factory";
				type = "IndustrialSite";
			};
			class Area_NemskFac
			{
				name = "Factory";
				type = "IndustrialSite";
			};
			class Area_TaraSaw
			{
				name = "Sawmill";
				type = "IndustrialSite";
			};
			class Area_Hospital
			{
				name = "Hospital";
				type = "Local";
			};
			class Area_BridgeBrensk
			{
				name = "Brensk Bridge";
				type = "Local";
			};
			class Area_BridgeTara
			{
				name = "Tara Bridge";
				type = "Local";
			};
			class Marine_Tara
			{
				name = "Tara Strait";
				type = "Marine";
			};
			class Marine_Brensk
			{
				name = "Brensk Bay";
				type = "Marine";
			};
			class Marine_Seraja
			{
				name = "Seraja Bay";
				type = "Marine";
			};
			class Marine_Lubjansk
			{
				name = "Lubjansk Bay";
				type = "Marine";
			};
			class Marine_Nemsk
			{
				name = "Nemsk Bay";
				type = "Marine";
			};
			class Marine_Sebjan
			{
				name = "Sebjan Reservoir";
				type = "Marine";
			};
			class Marine_SebjanMarsh
			{
				name = "Sebjan Marsh";
				type = "Marine";
			};
			class Marine_BrenskMarsh
			{
				name = "Brensk Marsh";
				type = "Marine";
			};
			class Hill_Tara
			{
				name = "TARA";
				type = "Hill";
			};
			class Hill_Nitija
			{
				name = "NITIJA";
				type = "Hill";
			};
			class Hill_Seraja
			{
				name = "SERAJA";
				type = "Hill";
			};
			class Hill_Ledjanaja
			{
				name = "Ledjanaja";
				type = "Hill";
			};
		};
	};
};

class CfgLocationTypes
{
	class Name
	{
		name = "keypoint";
		drawStyle = "name";
		texture = "#(argb,1,1,1)color(0.15,0.15,0.12,0.80)";
		color[] = {0.984, 0.831, 0.541,0.99};
		size = 0;
		font = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
		textSize = 0.033;
		shadow = 0;
		importance = 1;
	};
	class NameIcon
	{
		name = "keypoint";
		drawStyle = "icon";
		texture = "#(argb,1,1,1)color(0.15,0.15,0.25,0.50)";
		color[] = {0.984, 0.831, 0.541,0.95};
		size = 0;
		font = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
		textSize = 0.048;
		shadow = 0;
		importance = 1;
	};
	class Capital: Name
	{
		color[] = {0.262, 0.749, 0.941,1};
		importance = 7;
		textSize = 0.08;
	};
	class CapitalShadow: Name
	{
		color[] = {0.839, 0.839, 0.839,0.7};
		importance = 6;
		textSize = 0.083;
	};
	class City: Name
	{
		color[] = {0.262, 0.749, 0.941,1};
		textSize = 0.065;
		importance = 6;
	};
	class CityShadow: City
	{
		color[] = {0.839, 0.839, 0.839,0.7};
		textSize = 0.068;
		importance = 5;
	};
	class Village: Name
	{
		color[] = {0.262, 0.749, 0.941,1};
		textSize = 0.046;
		importance = 4;
	};
	class VillageShadow: Village
	{
		color[] = {0.839, 0.839, 0.839,0.7};
		textSize = 0.049;
		importance = 4;
	};
	class Local: Name
	{
		color[] = {0.262, 0.749, 0.941,1};
		textSize = 0.046;
		importance = 2;
	};
	class Marine: Name
	{
		color[] = {0.05,0.4,0.6,0.95};
		textSize = 0.042;
		importance = 3;
	};
	class Ruin: NameIcon
	{
		texture = "\DZ\gear\navigation\data\map_ruin_ca.paa";
		textSize = 0.035;
		importance = 3;
		size = 8;
	};
	class Camp: NameIcon
	{
		color[] = {0.698, 0.980, 0.619,1};
		texture = "\DZ\gear\navigation\data\map_camp_ca.paa";
		textSize = 0.042;
		importance = 3;
		size = 9;
	};
	class Hill: NameIcon
	{
		color[] = {0.698, 0.980, 0.619,1};
		texture = "\DZ\gear\navigation\data\map_hill_ca.paa";
		textSize = 0.042;
		importance = 6;
		size = 8;
	};
	class ViewPoint: NameIcon
	{
		color[] = {0.698, 0.980, 0.619,1};
		texture = "\DZ\gear\navigation\data\map_viewpoint_ca.paa";
		textSize = 0.042;
		importance = 6;
		size = 8;
	};
	class RockArea: NameIcon
	{
		color[] = {0.541, 0.921, 0.984,0.9};
		texture = "\DZ\gear\navigation\data\map_rock_ca.paa";
		size = 8;
	};
	class RailroadStation: NameIcon
	{
		color[] = {0.541, 0.921, 0.984,0.9};
		texture = "\DZ\gear\navigation\data\map_station_ca.paa";
		size = 7;
	};
	class IndustrialSite: NameIcon
	{
		color[] = {0.541, 0.921, 0.984,0.9};
		texture = "\DZ\gear\navigation\data\map_factory_ca.paa";
		size = 7;
	};
	class LocalOffice: NameIcon
	{
		color[] = {0.541, 0.921, 0.984,0.9};
		texture = "\DZ\gear\navigation\data\map_govoffice_ca.paa";
		size = 7;
	};
	class BorderCrossing: NameIcon
	{
		color[] = {0.541, 0.921, 0.984,0.9};
		texture = "\DZ\gear\navigation\data\map_border_cross_ca.paa";
		size = 7;
	};
	class MilitaryBase: Name
	{
		color[] = {0.970,0.239,0.314,1};
		textSize = 0.054;
		importance = 5;
	};
	class MilitaryBaseShadow: MilitaryBase
	{
		color[] = {0.870,0.870,0.870,0.7};
		textSize = 0.056;
		importance = 5;
	};
	class MilitaryOutpost: Name
	{
		color[] = {0.970,0.239,0.314,1};
		textSize = 0.048;
		importance = 4;
	};
	class MilitaryOutpostShadow: MilitaryOutpost
	{
		color[] = {0.870,0.870,0.870,0.7};
		textSize = 0.051;
		importance = 4;
	};
};



class RscMapControl
{
	scaleMin = 0.01;
	scaleMax = 0.95;
	ptsPerSquareSea = 8;
	ptsPerSquareTxt = 10;
	ptsPerSquareCLn = 10;
	ptsPerSquareExp = 10;
	ptsPerSquareCost = 10;
	ptsPerSquareFor = 9;
	ptsPerSquareForEdge = 12;
	ptsPerSquareRoad = 4;
	ptsPerSquareObj = 12;
	scaleDefault = 0.42;
	maxSatelliteAlpha = 1;
	alphaFadeStartScale = 2;
	alphaFadeEndScale = 2;
	userMapPath = "";
	maxUserMapAlpha = 0.00;
	alphaUserMapFadeStartScale = 1;
	alphaUserMapFadeEndScale = 1;
	showCountourInterval = 1;
	colorBackground[] = {0.0,0.0,0.0,0.0};
	colorSea[] = {0.466, 0.533, 0.776,0.33};
	colorForest[] = {0.302, 0.647, 0.208,0.05};
	colorForestBorder[] = {0.0,0.0,0.0,0.0};
	colorRocks[] = {0.541,0.541,0.541,0.4};
	colorRocksBorder[] = {0.0,0.0,0.0,0.0};
	colorLevels[] = {0.286,0.177,0.094,0.5};
	colorMainCountlines[] = {0.572,0.354,0.188,0.5};
	colorCountlines[] = {0.572,0.354,0.188,0.0};
	colorMainCountlinesWater[] = {0.491,0.577,0.702,0.6};
	colorCountlinesWater[] = {0.491,0.577,0.702,0.3};
	colorPowerLines[] = {0.05,0.05,0.05,0.8};
	colorRailWay[] = {0.6,0.15,0.0,0.95};
	colorNames[] = {0.1,0.1,0.1,0.9};
	colorInactive[] = {1.0,1.0,1.0,0.0};
	colorOutside[] = {0.0,0.0,0.0,1.0};
	colorTracks[] = {0.84,0.76,0.65,0.80};
	colorTracksFill[] = {0.84,0.76,0.65,0.5};
	colorRoads[] = {0.6,0.6,0.6,0.95};
	colorRoadsFill[] = {1.0,1.0,1.0,0.85};
	colorMainRoads[] = {0.9,0.5,0.3,0.95};
	colorMainRoadsFill[] = {1.0,0.6,0.4,0.90};
	colorGrid[] = {0.1,0.1,0.1,0.5};
	colorGridMap[] = {0.1,0.1,0.1,0.5};
	colorTrails[] = {0.84,0.76,0.65,0.20};
	colorTrailsFill[] = {0.84,0.76,0.65,0.60};
	colorMountPoint[] = {0.44,0.38,0.23,0.99};
	fontLabel = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontGrid = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	sizeExGrid = 0.03;
	fontUnits = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontNames = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	sizeExNames = 0.052;
	fontInfo = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontLevel = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	text = "#(argb,8,8,3)color(0.95,0.95,0.95,0.95)";
	class Legend
	{
		x = 0.0;
		y = 0.0;
		w = 0.0;
		h = 0.0;
		font = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
		sizeEx = 0.02;
		colorBackground[] = {1,1,1,0.0};
		color[] = {0.1,0.1,0.1,0.0};
	};
	class Bush
	{
		icon = "\dz\gear\navigation\data\map_bush_ca.paa";
		color[] = {0.302, 0.647, 0.208,0.25};
		size = 14;
		importance = "0.2 * 10 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class SmallTree
	{
		icon = "\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[] = {0.302, 0.647, 0.208,0.25};
		size = 12;
		importance = "0.6 * 8 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Tree
	{
		icon = "\dz\gear\navigation\data\map_tree_ca.paa";
		color[] = {0.302, 0.647, 0.208,0.25};
		size = 12;
		importance = "0.6 * 8 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Waterpump
	{
		icon = "BasicMap\gui\images\well.paa";
		color[] = {0.208,0.302,0.647,0.8};
		size = 16;
		importance = "1 * 20 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class Hospital
	{
		icon = "BasicMap\gui\images\hospital.paa";
		color[] = {1.0,0.14,0.50,0.6};
		size = 18;
		importance = "2 * 20 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class Store
	{
		icon = "\dz\gear\navigation\data\map_store_ca.paa";
		color[] = {1,1,1,0.6};
		size = 18;
		importance = "2 * 20 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class Police
	{
		icon = "BasicMap\gui\images\police.paa";
		color[] = {0.09,0.09,0.20,0.6};
		size = 18;
		importance = "2 * 20 * 0.05";
		coefMin = 0.1;
		coefMax = 2;
	};
	class FireDep
	{
		icon = "\dz\gear\navigation\data\map_firedep_ca.paa";
		color[] = {0.764,0,0,0.6};
		size = 18;
		importance = "2 * 20 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Rocks
	{
		icon = "\dz\gear\navigation\data\map_rock_ca.paa";
		color[] = {0.1,0.1,0.1,0.6};
		size = 12;
		importance = "0.5 * 12 * 0.05";
		coefMin = 0.25;
		coefMax = 4;
	};
};


class MapDefaults
{
	scaleMin = 0.01;
	scaleMax = 0.95;
	ptsPerSquareSea = 8;
	ptsPerSquareTxt = 10;
	ptsPerSquareCLn = 10;
	ptsPerSquareExp = 10;
	ptsPerSquareCost = 10;
	ptsPerSquareFor = 9;
	ptsPerSquareForEdge = 12;
	ptsPerSquareRoad = 4;
	ptsPerSquareObj = 12;
	scaleDefault = 0.42;
	maxSatelliteAlpha = 1;
	alphaFadeStartScale = 2;
	alphaFadeEndScale = 2;
	userMapPath = "";
	maxUserMapAlpha = 0.00;
	alphaUserMapFadeStartScale = 1;
	alphaUserMapFadeEndScale = 1;
	showCountourInterval = 1;
	colorBackground[] = {0.0,0.0,0.0,0.0};
	colorSea[] = {0.466, 0.533, 0.776,0.33};
	colorForest[] = {0.302, 0.647, 0.208,0.05};
	colorForestBorder[] = {0.0,0.0,0.0,0.0};
	colorRocks[] = {0.541,0.541,0.541,0.4};
	colorRocksBorder[] = {0.0,0.0,0.0,0.0};
	colorLevels[] = {0.286,0.177,0.094,0.5};
	colorMainCountlines[] = {0.572,0.354,0.188,0.5};
	colorCountlines[] = {0.572,0.354,0.188,0.0};
	colorMainCountlinesWater[] = {0.491,0.577,0.702,0.6};
	colorCountlinesWater[] = {0.491,0.577,0.702,0.3};
	colorPowerLines[] = {0.05,0.05,0.05,0.8};
	colorRailWay[] = {0.6,0.15,0.0,0.95};
	colorNames[] = {0.1,0.1,0.1,0.9};
	colorInactive[] = {1.0,1.0,1.0,0.0};
	colorOutside[] = {0.0,0.0,0.0,1.0};
	colorTracks[] = {0.84,0.76,0.65,0.80};
	colorTracksFill[] = {0.84,0.76,0.65,0.5};
	colorRoads[] = {0.6,0.6,0.6,0.95};
	colorRoadsFill[] = {1.0,1.0,1.0,0.85};
	colorMainRoads[] = {0.9,0.5,0.3,0.95};
	colorMainRoadsFill[] = {1.0,0.6,0.4,0.90};
	colorGrid[] = {0.1,0.1,0.1,0.5};
	colorGridMap[] = {0.1,0.1,0.1,0.5};
	colorTrails[] = {0.84,0.76,0.65,0.20};
	colorTrailsFill[] = {0.84,0.76,0.65,0.60};
	colorMountPoint[] = {0.44,0.38,0.23,0.99};
	fontLabel = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontGrid = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	sizeExGrid = 0.03;
	fontUnits = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontNames = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	sizeExNames = 0.052;
	fontInfo = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontLevel = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	text = "#(argb,8,8,3)color(0.95,0.95,0.95,0.95)";
	class Legend
	{
		x = 0.0;
		y = 0.0;
		w = 0.0;
		h = 0.0;
		font = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
		sizeEx = 0.02;
		colorBackground[] = {1,1,1,0.0};
		color[] = {0.1,0.1,0.1,0.0};
	};
	class Bush
	{
		icon = "\dz\gear\navigation\data\map_bush_ca.paa";
		color[] = {0.302, 0.647, 0.208,0.25};
		size = 14;
		importance = "0.2 * 10 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class SmallTree
	{
		icon = "\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[] = {0.302, 0.647, 0.208,0.25};
		size = 12;
		importance = "0.6 * 8 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Tree
	{
		icon = "\dz\gear\navigation\data\map_tree_ca.paa";
		color[] = {0.302, 0.647, 0.208,0.25};
		size = 12;
		importance = "0.6 * 8 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Waterpump
	{
		icon = "BasicMap\gui\images\well.paa";
		color[] = {0.208,0.302,0.647,0.8};
		size = 16;
		importance = "1 * 20 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class Hospital
	{
		icon = "BasicMap\gui\images\hospital.paa";
		color[] = {1.0,0.14,0.50,0.6};
		size = 18;
		importance = "2 * 20 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class Store
	{
		icon = "\dz\gear\navigation\data\map_store_ca.paa";
		color[] = {1,1,1,0.6};
		size = 18;
		importance = "2 * 20 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class Police
	{
		icon = "BasicMap\gui\images\police.paa";
		color[] = {0.09,0.09,0.20,0.6};
		size = 18;
		importance = "2 * 20 * 0.05";
		coefMin = 0.1;
		coefMax = 2;
	};
	class FireDep
	{
		icon = "\dz\gear\navigation\data\map_firedep_ca.paa";
		color[] = {0.764,0,0,0.6};
		size = 18;
		importance = "2 * 20 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Rocks
	{
		icon = "\dz\gear\navigation\data\map_rock_ca.paa";
		color[] = {0.1,0.1,0.1,0.6};
		size = 12;
		importance = "0.5 * 12 * 0.05";
		coefMin = 0.25;
		coefMax = 4;
	};
};