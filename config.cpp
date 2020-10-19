class CfgPatches
{
	class BasicMap
	{
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Worlds_Chernarusplus_World"};
	};
};

class CfgMods
{
	class BasicMap
	{
		dir="BasicMap";
        name="BasicMap";
        credits="DaemonForge";
        author="DaemonForge";
        authorID="0";
        version="0.1";
        extra=0;
        type="mod";
		inputs = "BasicMap/data/Inputs.xml";
	    dependencies[]={ "Game", "World", "Mission"};
	    class defs
	    {
			class gameScriptModule
            {
				value = "";
                files[]={
					"BasicMap/scripts/Common",
					"BasicMap/scripts/3_Game"
					};
            };
			
			class worldScriptModule
            {
                value="";
                files[]={ 
					"BasicMap/scripts/Common",
					"BasicMap/scripts/4_World" 
				};
            };
			
	        class missionScriptModule
            {
                value="";
                files[]={
					"BasicMap/scripts/Common",
					"BasicMap/scripts/5_Mission" 
				};
            };
        };
    };
};

class CfgWorlds
{
	class Names;
	class CAWorld;
	class ChernarusPlus: CAWorld
	{
		class Names
		{
			class Settlement_Chernogorsk
			{
				name = "CHERNOGORSK";
			};
			class Settlement_Novodmitrovsk
			{
				name = "NOVODMITROVSK";
			};
			class Settlement_Novoselki
			{
				name = "NOVOSELKI";
			};
			class Settlement_Dubovo
			{
				name = "DUBOVO";
			};
			class Settlement_Vysotovo
			{
				name = "VYSOTOVO";
			};
			class Settlement_Zelenogorsk
			{
				name = "ZELENOGORSK";
			};
			class Settlement_Berezino
			{
				name = "BEREZINO";
			};
			class Settlement_Elektrozavodsk
			{
				name = "ELEKTROZAVODSK";
			};
			class Settlement_NovayaPetrovka
			{
				name = "NOVAYA PETROVKA";
			};
			class Settlement_Gorka
			{
				name = "GORKA";
			};
			class Settlement_Solnechny
			{
				name = "SOLNECHNY";
			};
			class Settlement_StarySobor
			{
				name = "STARY SOBOR";
			};
			class Settlement_Vybor
			{
				name = "VYBOR";
			};
			class Settlement_Severograd
			{
				name = "SEVEROGRAD";
			};
			class Settlement_Bor
			{
				name = "BOR";
			};
			class Settlement_Svetloyarsk
			{
				name = "SVETLOYARSK";
			};
			class Settlement_Krasnostav
			{
				name = "KRASNOSTAV";
			};
			class Settlement_ChernayaPolyana
			{
				name = "CHERNAYA POLYANA";
			};
			class Settlement_Polyana
			{
				name = "POLYANA";
			};
			class Settlement_Tulga
			{
				name = "TULGA";
			};
			class Settlement_Msta
			{
				name = "MSTA";
			};
			class Settlement_Staroye
			{
				name = "STAROYE";
			};
			class Settlement_Shakhovka
			{
				name = "SHAKHOVKA";
			};
			class Settlement_Dolina
			{
				name = "DOLINA";
			};
			class Settlement_Orlovets
			{
				name = "ORLOVETS";
			};
			class Settlement_NovySobor
			{
				name = "NOVY SOBOR";
			};
			class Settlement_Kabanino
			{
				name = "KABANINO";
			};
			class Settlement_Mogilevka
			{
				name = "MOGILEVKA";
			};
			class Settlement_Nadezhdino
			{
				name = "NADEZHDINO";
			};
			class Settlement_Guglovo
			{
				name = "GUGLOVO";
			};
			class Settlement_Kamyshovo
			{
				name = "KAMYSHOVO";
			};
			class Settlement_Pusta
			{
				name = "PUSTA";
			};
			class Settlement_Dubrovka
			{
				name = "DUBROVKA";
			};
			class Settlement_VyshnayaDubrovka
			{
				name = "VYSHNAYA DUBROVKA";
			};
			class Settlement_Khelm
			{
				name = "KHELM";
			};
			class Settlement_Olsha
			{
				name = "OLSHA";
			};
			class Settlement_Gvozdno
			{
				name = "GVOZDNO";
			};
			class Settlement_Grishino
			{
				name = "GRISHINO";
			};
			class Settlement_Rogovo
			{
				name = "ROGOVO";
			};
			class Settlement_Pogorevka
			{
				name = "POGOREVKA";
			};
			class Settlement_Pustoshka
			{
				name = "PUSTOSHKA";
			};
			class Settlement_Kozlovka
			{
				name = "KOZLOVKA";
			};
			class Settlement_Karmanovka
			{
				name = "KARMANOVKA";
			};
			class Settlement_Balota
			{
				name = "BALOTA";
			};
			class Settlement_Komarovo
			{
				name = "KOMOROVO";
			};
			class Settlement_Kamenka
			{
				name = "KAMENKA";
			};
			class Settlement_Myshkino
			{
				name = "MYSHKINO";
			};
			class Settlement_Pavlovo
			{
				name = "PAVLOVO";
			};
			class Settlement_Lopatino
			{
				name = "LOPATINO";
			};
			class Settlement_Vyshnoye
			{
				name = "VYSHNOYE";
			};
			class Settlement_Prigorodki
			{
				name = "PRIGORODKI";
			};
			class Settlement_Drozhino
			{
				name = "DROZHINO";
			};
			class Settlement_Sosnovka
			{
				name = "SOSNOVKA";
			};
			class Settlement_Nizhneye
			{
				name = "NIZHNEYE";
			};
			class Settlement_Pulkovo
			{
				name = "PULKOVO";
			};
			class Settlement_Berezhki
			{
				name = "BEREZHKI";
			};
			class Settlement_Turovo
			{
				name = "TUROVO";
			};
			class Settlement_BelayaPolyana
			{
				name = "BELAYA POLYANA";
			};
			class Settlement_Dobroye
			{
				name = "DOBROYE";
			};
			class Settlement_Nagornoye
			{
				name = "NAGORNOYE";
			};
			class Settlement_Svergino
			{
				name = "SVERGINO";
			};
			class Settlement_Ratnoye
			{
				name = "RATNOYE";
			};
			class Settlement_Kamensk
			{
				name = "KAMENSK";
			};
			class Settlement_Krasnoye
			{
				name = "KRASNOYE";
			};
			class Settlement_StaryYar
			{
				name = "STARY YAR";
			};
			class Settlement_Polesovo
			{
				name = "POLESOVO";
			};
			class Settlement_Tisy
			{
				name = "TISY";
			};
			class Settlement_Topolniki
			{
				name = "TOPOLNIKI";
			};
			class Settlement_Zaprudnoye
			{
				name = "ZAPRUDNOYE";
			};
			class Settlement_Sinystok
			{
				name = "SINYSTOK";
			};
			class Settlement_Vavilovo
			{
				name = "VAVILOVO";
			};
			class Settlement_Kumyrna
			{
				name = "KUMYRNA";
			};
			class Settlement_Kalinovka
			{
				name = "KALINOVKA";
			};
			class Settlement_Bogatyrka
			{
				name = "BOGATYRKA";
			};
			class Settlement_Zvir
			{
				name = "ZVIR";
			};
			class Settlement_Zabolotye
			{
				name = "ZABOLOTYE";
			};
			class Settlement_Galkino
			{
				name = "GALKINO";
			};
			class Settlement_SvyatoyRomanSkiResort
			{
				name = "Ski Resort";
			};
			class Settlement_SKVSChBiathlonArena
			{
				name = "Biathlon Arena";
			};
			class Camp_Arsenovo
			{
				name = "Camp Arsenovo";
			};
			class Camp_Stroytel
			{
				name = "Camp Stroytel";
			};
			class Camp_Romashka
			{
				name = "Camp Romashka";
			};
			class Camp_Kometa
			{
				name = "Camp Kometa";
			};
			class Camp_Druzhba
			{
				name = "Camp Druzhba";
			};
			class Camp_Nadezhda
			{
				name = "Camp Nadezhda";
			};
			class Camp_YouthPioneer
			{
				name = "Youth Pioneer Camp";
			};
			class Camp_ProudChernarus
			{
				name = "Proud Chernarus Camp";
			};
			class Camp_Shkolnik
			{
				name = "Shkolnik Camp";
			};
			class Camp_Pobeda
			{
				name = "Pobeda Camp";
			};
			class Camp_Metalurg
			{
				name = "Metalurg Camp";
			};
			class Hill_Zelenayagora
			{
				name = "ZELENAYA";
			};
			class Local_Dichina
			{
				name = "DICHINA";
			};
			class Local_Novylug
			{
				name = "NOVY LUG";
			};
			class Local_Staryeluga
			{
				name = "STARYE LUGA";
			};
			class Hill_Vysota
			{
				name = "VYSOTA";
			};
			class Hill_Kopyto
			{
				name = "KOPYTO";
			};
			class Local_Grubyeskaly
			{
				name = "GRUBYE SKALY";
			};
			class Local_Chernyles
			{
				name = "CHERNY LES";
			};
			class Hill_Altar
			{
				name = "ALTAR";
			};
			class Local_RadioZenit
			{
				name = "ZENIT";
			};
			class Hill_PikKozlova
			{
				name = "PIK KOZLOVA";
			};
			class Local_Pustoykhrebet
			{
				name = "PUSTOY KHREBET";
			};
			class Hill_Bashnya
			{
				name = "BASHNYA";
			};
			class Hill_Veresnik
			{
				name = "VERESNIK";
			};
			class Hill_Kurgan
			{
				name = "KURGAN";
			};
			class Hill_Kustryk
			{
				name = "KUSTRYK";
			};
			class Hill_Vetryanayagora
			{
				name = "VETRYANAYA";
			};
			class Hill_Kalmyk
			{
				name = "KALMYK";
			};
			class Hill_PopIvan
			{
				name = "POP IVAN";
			};
			class Hill_Erbenka
			{
				name = "ERBENKA";
			};
			class Local_Lesnoykhrebet
			{
				name = "LESNOY KHREBET";
			};
			class Hill_Vysokiykamen
			{
				name = "VYSOKIY KAMEN";
			};
			class Hill_Dobry
			{
				name = "DOBRY";
			};
			class Hill_Baranchik
			{
				name = "BARANCHIK";
			};
			class Hill_Malinovka
			{
				name = "MALINOVKA";
			};
			class Hill_Dubina
			{
				name = "DUBINA";
			};
			class Hill_Klen
			{
				name = "KLEN";
			};
			class Hill_Chernayagora
			{
				name = "CHERNAYA";
			};
			class Ruin_Zolotar
			{
				name = "ZOLOTAR";
			};
			class Hill_Ostry
			{
				name = "OSTRY";
			};
			class Hill_Olsha
			{
				name = "OLSHA";
			};
			class Hill_Lysayagora
			{
				name = "LYSAYA";
			};
			class Hill_Tumannyverkh
			{
				name = "TUMANNY";
			};
			class Hill_Shishok
			{
				name = "SHISHOK";
			};
			class Hill_Kikimora
			{
				name = "KIKIMORA";
			};
			class Hill_BolshoyKotel
			{
				name = "BOLSHOY KOTEL";
			};
			class Hill_Simurg
			{
				name = "SIMURG";
			};
			class Hill_Volchiypik
			{
				name = "VOLVHIY PIK";
			};
			class Hill_Sokol
			{
				name = "SOKOL";
			};
			class Hill_Viselitsa
			{
				name = "VISELITSA";
			};
			class Hill_SvyatoyRoman
			{
				name = "SVYATOY ROMAN";
			};
			class Hill_Koman
			{
				name = "KOMAN";
			};
			class Hill_Mayak
			{
				name = "MAYAK";
			};
			class Marine_Tikhiyzaliv
			{
				name = "Tikhiy Bay";
			};
			class Marine_Mutnyizaliv
			{
				name = "Tikhiy Bay";
			};
			class Marine_Chernyzaliv
			{
				name = "Cherny Bay";
			};
			class Marine_Zelenyzaliv
			{
				name = "Zeleny Bay";
			};
			class Marine_Skalistyproliv
			{
				name = "Skalisty Pass";
			};
			class Marine_Nizhniyzaliv
			{
				name = "Nizhniy Bay";
			};
			class Marine_ZalivGuba
			{
				name = "Zaliv Guba";
			};
			class Marine_Rify
			{
				name = "Rify";
			};
			class Marine_Ivovoyeozero
			{
				name = "Ivovoye Lake";
			};
			class Marine_Chernoyeozero
			{
				name = "Chernoye Lake";
			};
			class Marine_PlotinaTopolka
			{
				name = "Topolka Dam";
			};
			class Marine_PlotinaPobeda
			{
				name = "Pobeda Dam";
			};
			class Marine_PlotinaTishina
			{
				name = "Tishina Dam";
			};
			class Marine_Ozerko
			{
				name = "Ozerko";
			};
			class Marine_Prud
			{
				name = "Prud";
			};
			class Ruin_Chortovzamok
			{
				name = "Chortov Castle";
			};
			class Ruin_Zub
			{
				name = "Zub Castle";
			};
			class Ruin_Rog
			{
				name = "Rog Castle";
			};
			class Ruin_Gnomovzamok
			{
				name = "Gnomov Castle";
			};
			class Local_Grozovypereval
			{
				name = "Grozovy Pass";
			};
			class Local_Sosnovypereval
			{
				name = "Sosnovy Pass";
			};
			class Local_PerevalOreshka
			{
				name = "Oreshka Pass";
			};
			class Local_Turovskiypereval
			{
				name = "Turovskiy Pass";
			};
			class Local_Tridoliny
			{
				name = "Tri Doliny";
			};
			class Local_Grozovyedoly
			{
				name = "Grozovye Doly";
			};
			class Ruin_Klyuch
			{
				name = "Klyuch";
			};
			class Marine_Glubokoyeozero
			{
				name = "Glubokoye Lake";
			};
			class Local_Skalka
			{
				name = "Skalka";
			};
			class Local_Vidy
			{
				name = "Vidy";
			};
			class Local_Adamovka
			{
				name = "Adamovka";
			};
			class Settlement_Skalisty
			{
				name = "Skalisty";
			};
			class Ruin_Storozh
			{
				name = "Storozh";
			};
			class Local_Drakon
			{
				name = "Drakon";
			};
			class Local_Otmel
			{
				name = "Otmel";
			};
			class Local_MysGolova
			{
				name = "Cape Golova";
			};
			class Local_MysKrutoy
			{
				name = "Cape Krutoy";
			};
			class Hill_Tokarnya
			{
				name = "Tokarnya";
			};
			class Hill_Ostrog
			{
				name = "Ostrog";
			};
			class Local_Maryanka
			{
				name = "Maryanka";
			};
			class Local_Polonina
			{
				name = "Polonina";
			};
			class Local_Kalinka
			{
				name = "Kalinka";
			};
			class Ruin_Krona
			{
				name = "Krona Castle";
			};
			class Local_TriKresta
			{
				name = "Tri Kresta";
			};
			class Local_Rostoki
			{
				name = "Rostoki";
			};
			class Marine_OrlyeOzero
			{
				name = "Orlye Ozero";
			};
			class Local_Makosh
			{
				name = "Makosh";
			};
			class Local_Klenovyipereval
			{
				name = "Klenovyi pereval";
			};
			class Local_Zmeinykhrebet
			{
				name = "Zmeiny khrebet";
			};
			class Local_Krutyeskaly
			{
				name = "Krutye skaly";
			};
			class Local_Bogat
			{
				name = "Bogat";
			};
			class Local_Dubnik
			{
				name = "Dubnik";
			};
			class Local_Dazhbog
			{
				name = "Dazhbog";
			};
			class Marine_Verbnik
			{
				name = "Verbnik";
			};
			class Local_Medvezhilugi
			{
				name = "Medvezhi lugi";
			};
			class Ruin_Voron
			{
				name = "Voron";
			};
			class Marine_Glaza
			{
				name = "Glaza";
			};
			class Local_KarerKrasnayaZarya
			{
				name = "Karer Krasnaya Zarya";
			};
			class Local_Matveyevo
			{
				name = "Matveyevo";
			};
			class Local_Kotka
			{
				name = "Kotka";
			};
			class Local_Chernyeskaly
			{
				name = "Chernye skaly";
			};
			class Local_MB_VMC
			{
				name = "Veresnik Military Camp(VMC)";
			};
			class Local_MB_Tisy
			{
				name = "Tisy Military Base";
			};
			class Local_MB_Kamensk
			{
				name = "Kamensk Military Base";
			};
			class Local_MB_Zeleno
			{
				name = "Zelenogorsk Military Outpost";
			};
			class Local_MB_Pavlovo
			{
				name = "Pavlovo Military Base";
			};
			class Local_AF_Balota
			{
				name = "Balota Airfield";
			};
			class Local_AF_Krasno
			{
				name = "Krasno Airfield";
			};
			class Local_AF_Vybor
			{
				name = "Vybor Airfield";
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
		texture = "#(argb,1,1,1)color(0.15,0.15,0.12,0.85)";
		color[] = {0.25,0.25,0.35,0.99};
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
		texture = "#(argb,1,1,1)color(0.15,0.15,0.25,0.99)";
		color[] = {0.20,0.20,0.32,0.95};
		size = 0;
		font = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
		textSize = 0.048;
		shadow = 0;
		importance = 1;
	};
	class Capital: Name
	{
		color[] = {0.15,0.15,0.35,0.99};
		textSize = 0.08;
		importance = 7;
	};
	class City: Name
	{
		color[] = {0.17,0.17,0.39,0.95};
		textSize = 0.055;
		importance = 6;
	};
	class Village: Name
	{
		color[] = {0.3,0.38,0.48,0.95};
		textSize = 0.046;
		importance = 4;
	};
	class Local: Name
	{
		color[] = {0.3,0.38,0.48,0.95};
		textSize = 0.035;
		importance = 2;
	};
	class Marine: Name
	{
		color[] = {0.05,0.4,0.6,0.8};
		textSize = 0.03;
		importance = 2;
	};
	class Ruin: NameIcon
	{
		texture = "\DZ\gear\navigation\data\map_ruin_ca.paa";
		textSize = 0.03;
		importance = 2;
		size = 8;
	};
	class Camp: NameIcon
	{
		color[] = {0.44,0.38,0.3,0.9};
		texture = "\DZ\gear\navigation\data\map_camp_ca.paa";
		textSize = 0.04;
		size = 9;
	};
	class Hill: NameIcon
	{
		color[] = {0.7,0.7,0.7,0.9};
		texture = "\DZ\gear\navigation\data\map_hill_ca.paa";
		size = 9;
	};
	class ViewPoint: NameIcon
	{
		color[] = {0.78,0,0.05,0.9};
		texture = "\DZ\gear\navigation\data\map_viewpoint_ca.paa";
		size = 8;
	};
	class RockArea: NameIcon
	{
		color[] = {1,1,1,0.9};
		texture = "\DZ\gear\navigation\data\map_rock_ca.paa";
		size = 8;
	};
	class RailroadStation: NameIcon
	{
		color[] = {1,1,1,0.9};
		texture = "\DZ\gear\navigation\data\map_station_ca.paa";
		size = 7;
	};
	class IndustrialSite: NameIcon
	{
		color[] = {1,1,1,0.9};
		texture = "\DZ\gear\navigation\data\map_factory_ca.paa";
		size = 7;
	};
	class LocalOffice: NameIcon
	{
		color[] = {0.22,0.21,0.51,0.9};
		texture = "\DZ\gear\navigation\data\map_govoffice_ca.paa";
		size = 7;
	};
	class BorderCrossing: NameIcon
	{
		color[] = {0.78,0,0.05,0.9};
		texture = "\DZ\gear\navigation\data\map_border_cross_ca.paa";
		size = 7;
	};
	class VegetationBroadleaf: NameIcon
	{
		color[] = {0.25,0.4,0.2,0.9};
		texture = "\DZ\gear\navigation\data\map_broadleaf_ca.paa";
		size = 6;
	};
	class VegetationFir: NameIcon
	{
		color[] = {0.25,0.4,0.2,0.9};
		texture = "\DZ\gear\navigation\data\map_fir_ca.paa";
		size = 6;
	};
	class VegetationPalm: NameIcon
	{
		color[] = {0.25,0.4,0.2,0.9};
		texture = "\DZ\gear\navigation\data\map_palm_ca.paa";
		size = 6;
	};
	class VegetationVineyard: NameIcon
	{
		color[] = {0.25,0.4,0.2,0.9};
		texture = "\DZ\gear\navigation\data\map_vineyard_ca.paa";
		size = 6;
	};
};



class MapDefaults
{
	scaleMin = 0.005;
	scaleMax = 0.90;
	ptsPerSquareSea = 8;
	ptsPerSquareTxt = 10;
	ptsPerSquareCLn = 10;
	ptsPerSquareExp = 10;
	ptsPerSquareCost = 10;
	ptsPerSquareFor = 9;
	ptsPerSquareForEdge = 15;
	ptsPerSquareRoad = 4;
	ptsPerSquareObj = 15;
	scaleDefault = 0.65;
	maxSatelliteAlpha = 0.70;
	alphaFadeStartScale = 2;
	alphaFadeEndScale = 2;
	userMapPath = "";
	maxUserMapAlpha = 0.7;
	alphaUserMapFadeStartScale = 0.5;
	alphaUserMapFadeEndScale = 1;
	showCountourInterval = 1;
	colorBackground[] = {0.971,0.96,0.952,0.00};
	colorSea[] = {0.467,0.631,0.851,0.5};
	colorForest[] = {0.42,0.51,0.27,0.7};
	colorForestBorder[] = {0.0,0.0,0.0,0.0};
	colorRocks[] = {0.1,0.1,0.1,0.4};
	colorRocksBorder[] = {0.0,0.0,0.0,0.0};
	colorLevels[] = {0.286,0.177,0.094,0.5};
	colorMainCountlines[] = {0.572,0.354,0.188,0.5};
	colorCountlines[] = {0.572,0.354,0.188,0.0};
	colorMainCountlinesWater[] = {0.491,0.577,0.702,0.6};
	colorCountlinesWater[] = {0.491,0.577,0.702,0.3};
	colorPowerLines[] = {0.05,0.05,0.05,0.8};
	colorRailWay[] = {0.8,0.2,0.0,0.95};
	colorNames[] = {0.1,0.1,0.1,0.9};
	colorInactive[] = {1.0,1.0,1.0,0.0};
	colorOutside[] = {0.0,0.0,0.0,1.0};
	colorTracks[] = {0.84,0.76,0.65,0.15};
	colorTracksFill[] = {0.84,0.76,0.65,1.0};
	colorRoads[] = {0.6,0.6,0.6,0.95};
	colorRoadsFill[] = {1.0,1.0,1.0,0.9};
	colorMainRoads[] = {0.9,0.5,0.3,0.90};
	colorMainRoadsFill[] = {1.0,0.6,0.4,0.95};
	colorGrid[] = {0.1,0.1,0.1,0.5};
	colorGridMap[] = {0.1,0.1,0.1,0.5};
	colorTrails[] = {0.84,0.76,0.65,0.20};
	colorTrailsFill[] = {0.84,0.76,0.65,0.60};
	colorMountPoint[] = {0.44,0.38,0.23,0.99};
	fontLabel = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontGrid = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontUnits = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontNames = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	sizeExNames = 0.032;
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
		colorBackground[] = {1,1,1,0.2};
		color[] = {0.1,0.1,0.1,0.8};
	};
	class Bush
	{
		icon = "\dz\gear\navigation\data\map_bush_ca.paa";
		color[] = {0.32,0.42,0.20,0.85};
		size = 14;
		importance = "0.2 * 14 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class SmallTree
	{
		icon = "\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[] = {0.33,0.52,0.20,0.85};
		size = 12;
		importance = "0.6 * 12 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Rock
	{
		icon = "\dz\gear\navigation\data\map_rock_ca.paa";
		color[] = {0.18,0.18,0.18,0.85};
		size = 12;
		importance = "0.5 * 12 * 0.05";
		coefMin = 0.2;
		coefMax = 3;
	};
	class Fuelstation
	{
		icon = "\dz\gear\navigation\data\map_fuelstation_ca.paa";
		size = 14;
		color[] = {0.95,0.95,0.95,1};
		importance = "2 * 16 * 0.05";
		coefMin = 0.75;
		coefMax = 3;
	};
	class Lighthouse
	{
		icon = "\dz\gear\navigation\data\map_lighthouse_ca.paa";
		size = 8;
		color[] = {0.95,0.95,0.95,0.8};
		importance = "3 * 16 * 0.05";
		coefMin = 0.8;
		coefMax = 3;
	};
	class Stack
	{
		icon = "\dz\gear\navigation\data\map_stack_ca.paa";
		size = 10;
		color[] = {1,1,1,0.9};
		importance = "2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Transmitter
	{
		icon = "\dz\gear\navigation\data\map_transmitter_ca.paa";
		color[] = {1,1,1,0.9};
		size = 6;
		importance = "2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Watertower
	{
		icon = "\dz\gear\navigation\data\map_watertower_ca.paa";
		color[] = {0.2,0.45,0.7,0.9};
		size = 10;
		importance = "1.2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Shipwreck
	{
		icon = "\dz\gear\navigation\data\map_shipwreck_ca.paa";
		color[] = {1,1,1,0.9};
		size = 12;
		importance = "1.2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 3;
	};
	class Monument
	{
		icon = "\dz\gear\navigation\data\map_monument_ca.paa";
		color[] = {1,1,1,0.75};
		size = 16;
		importance = "1.2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class BusStop
	{
		icon = "\dz\gear\navigation\data\map_busstop_ca.paa";
		color[] = {0.15,0.26,0.87,0.85};
		size = 10;
		importance = "1 * 10 * 0.05";
		coefMin = 0.1;
		coefMax = 1;
	};
	class Fountain
	{
		icon = "\dz\gear\navigation\data\map_fountain_ca.paa";
		color[] = {0.2,0.45,0.7,1};
		size = 16;
		importance = "1 * 12 * 0.05";
		coefMin = 0.1;
		coefMax = 3;
	};
	class Waterpump
	{
		icon = "BasicMap\gui\images\well.paa";
		color[] = {0.2,0.45,0.7,1};
		size = 16;
		importance = "1 * 22 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class Hospital
	{
		icon = "BasicMap\gui\images\hospital.paa";
		color[] = {0.15,0.26,0.87,1};
		size = 18;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class Store
	{
		icon = "\dz\gear\navigation\data\map_store_ca.paa";
		color[] = {1,1,1,1};
		size = 18;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class Police
	{
		icon = "BasicMap\gui\images\police.paa";
		color[] = {0.09,0.09,0.20,0.8};
		size = 18;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 2;
	};
	class FireDep
	{
		icon = "\dz\gear\navigation\data\map_firedep_ca.paa";
		color[] = {0.764,0,0,0.8};
		size = 18;
		importance = "2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class TouristSign
	{
		icon = "\dz\gear\navigation\data\map_tsign_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 1;
	};
	class Tourism
	{
		icon = "\dz\gear\navigation\data\map_tourism_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 2;
	};
	class Cross
	{
		icon = "\dz\gear\navigation\data\map_cross_ca.paa";
		size = 12;
		color[] = {1,1,1,0.9};
		importance = "0.7 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 1;
	};
	class Chapel
	{
		icon = "\dz\gear\navigation\data\map_chapel_ca.paa";
		color[] = {1,1,1,0.9};
		size = 12;
		importance = "1 * 16 * 0.05";
		coefMin = 0.9;
		coefMax = 3;
	};
	class Church
	{
		icon = "\dz\gear\navigation\data\map_church_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2 * 16 * 0.05";
		coefMin = 0.9;
		coefMax = 4;
	};
	class ViewTower
	{
		icon = "\dz\gear\navigation\data\map_viewtower_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2.5 * 16 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class TouristShelter
	{
		icon = "\dz\gear\navigation\data\map_tshelter_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2 * 16 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class Quay
	{
		icon = "\dz\gear\navigation\data\map_quay_ca.paa";
		size = 16;
		color[] = {1,1,1,0.9};
		importance = "2 * 16 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class Bunker
	{
		icon = "\dz\gear\navigation\data\map_bunker_ca.paa";
		color[] = {1,1,1,0.9};
		size = 14;
		importance = "1.5 * 14 * 0.05";
		coefMin = 0.25;
		coefMax = 4;
	};
	class Fortress
	{
		icon = "\dz\gear\navigation\data\map_fortress_ca.paa";
		size = 16;
		color[] = {1,1,1,0.9};
		importance = "2 * 16 * 0.05";
		coefMin = 0.25;
		coefMax = 4;
	};
	class Rocks
	{
		icon = "\dz\gear\navigation\data\map_rock_ca.paa";
		color[] = {0.1,0.1,0.1,0.8};
		size = 12;
		importance = "0.5 * 12 * 0.05";
		coefMin = 0.25;
		coefMax = 4;
	};
	class Ruin
	{
		icon = "\dz\gear\navigation\data\map_ruin_ca.paa";
		size = 16;
		color[] = {1,1,1,0.9};
		importance = "1.2 * 16 * 0.05";
		coefMin = 1;
		coefMax = 4;
	};
};


class RscMapControl
{
	scaleMin = 0.005;
	scaleMax = 0.90;
	ptsPerSquareSea = 8;
	ptsPerSquareTxt = 10;
	ptsPerSquareCLn = 10;
	ptsPerSquareExp = 10;
	ptsPerSquareCost = 10;
	ptsPerSquareFor = 9;
	ptsPerSquareForEdge = 15;
	ptsPerSquareRoad = 4;
	ptsPerSquareObj = 15;
	scaleDefault = 0.65;
	maxSatelliteAlpha = 0.70;
	alphaFadeStartScale = 2;
	alphaFadeEndScale = 2;
	userMapPath = "";
	maxUserMapAlpha = 0.7;
	alphaUserMapFadeStartScale = 0.50;
	alphaUserMapFadeEndScale = 0.95;
	showCountourInterval = 1;
	colorBackground[] = {0.971,0.96,0.952,0.05};
	colorSea[] = {0.467,0.631,0.851,0.5};
	colorForest[] = {0.42,0.51,0.27,0.7};
	colorForestBorder[] = {0.0,0.0,0.0,0.0};
	colorRocks[] = {0.1,0.1,0.1,0.4};
	colorRocksBorder[] = {0.0,0.0,0.0,0.0};
	colorLevels[] = {0.286,0.177,0.094,0.5};
	colorMainCountlines[] = {0.572,0.354,0.188,0.5};
	colorCountlines[] = {0.572,0.354,0.188,0.0};
	colorMainCountlinesWater[] = {0.491,0.577,0.702,0.6};
	colorCountlinesWater[] = {0.491,0.577,0.702,0.3};
	colorPowerLines[] = {0.05,0.05,0.05,0.8};
	colorRailWay[] = {0.8,0.2,0.0,0.95};
	colorNames[] = {0.1,0.1,0.1,0.9};
	colorInactive[] = {1.0,1.0,1.0,0.0};
	colorOutside[] = {0.0,0.0,0.0,1.0};
	colorTracks[] = {0.84,0.76,0.65,0.15};
	colorTracksFill[] = {0.84,0.76,0.65,1.0};
	colorRoads[] = {0.6,0.6,0.6,0.95};
	colorRoadsFill[] = {1.0,1.0,1.0,0.9};
	colorMainRoads[] = {0.9,0.5,0.3,0.90};
	colorMainRoadsFill[] = {1.0,0.6,0.4,0.95};
	colorGrid[] = {0.1,0.1,0.1,0.5};
	colorGridMap[] = {0.1,0.1,0.1,0.5};
	colorTrails[] = {0.84,0.76,0.65,0.20};
	colorTrailsFill[] = {0.84,0.76,0.65,0.60};
	colorMountPoint[] = {0.44,0.38,0.23,0.99};
	fontLabel = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontGrid = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontUnits = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	fontNames = "BasicMap/gui/fonts/Oswald-Medium/Oswald-Medium26";
	sizeExNames = 0.032;
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
		colorBackground[] = {1,1,1,0.2};
		color[] = {0.1,0.1,0.1,0.8};
	};
	class Bush
	{
		icon = "\dz\gear\navigation\data\map_bush_ca.paa";
		color[] = {0.32,0.42,0.20,0.85};
		size = 14;
		importance = "0.2 * 14 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class SmallTree
	{
		icon = "\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[] = {0.33,0.52,0.20,0.85};
		size = 12;
		importance = "0.6 * 12 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Rock
	{
		icon = "\dz\gear\navigation\data\map_rock_ca.paa";
		color[] = {0.18,0.18,0.18,0.85};
		size = 12;
		importance = "0.5 * 12 * 0.05";
		coefMin = 0.2;
		coefMax = 3;
	};
	class Fuelstation
	{
		icon = "\dz\gear\navigation\data\map_fuelstation_ca.paa";
		size = 14;
		color[] = {0.95,0.95,0.95,1};
		importance = "2 * 16 * 0.05";
		coefMin = 0.75;
		coefMax = 3;
	};
	class Lighthouse
	{
		icon = "\dz\gear\navigation\data\map_lighthouse_ca.paa";
		size = 8;
		color[] = {0.95,0.95,0.95,0.8};
		importance = "3 * 16 * 0.05";
		coefMin = 0.8;
		coefMax = 3;
	};
	class Stack
	{
		icon = "\dz\gear\navigation\data\map_stack_ca.paa";
		size = 10;
		color[] = {1,1,1,0.9};
		importance = "2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Transmitter
	{
		icon = "\dz\gear\navigation\data\map_transmitter_ca.paa";
		color[] = {1,1,1,0.9};
		size = 6;
		importance = "2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Watertower
	{
		icon = "\dz\gear\navigation\data\map_watertower_ca.paa";
		color[] = {0.2,0.45,0.7,0.9};
		size = 10;
		importance = "1.2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class Shipwreck
	{
		icon = "\dz\gear\navigation\data\map_shipwreck_ca.paa";
		color[] = {1,1,1,0.9};
		size = 12;
		importance = "1.2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 3;
	};
	class Monument
	{
		icon = "\dz\gear\navigation\data\map_monument_ca.paa";
		color[] = {1,1,1,0.75};
		size = 16;
		importance = "1.2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class BusStop
	{
		icon = "\dz\gear\navigation\data\map_busstop_ca.paa";
		color[] = {0.15,0.26,0.87,0.85};
		size = 10;
		importance = "1 * 10 * 0.05";
		coefMin = 0.1;
		coefMax = 1;
	};
	class Fountain
	{
		icon = "\dz\gear\navigation\data\map_fountain_ca.paa";
		color[] = {0.2,0.45,0.7,1};
		size = 16;
		importance = "1 * 12 * 0.05";
		coefMin = 0.1;
		coefMax = 3;
	};
	class Waterpump
	{
		icon = "BasicMap\gui\images\well.paa";
		color[] = {0.2,0.45,0.7,1};
		size = 18;
		importance = "1 * 18 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class Hospital
	{
		icon = "BasicMap\gui\images\hospital.paa";
		color[] = {0.15,0.26,0.87,1};
		size = 18;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class Store
	{
		icon = "\dz\gear\navigation\data\map_store_ca.paa";
		color[] = {1,1,1,1};
		size = 18;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 4;
	};
	class Police
	{
		icon = "BasicMap\gui\images\police.paa";
		color[] = {0.09,0.09,0.20,0.8};
		size = 18;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 2;
	};
	class FireDep
	{
		icon = "\dz\gear\navigation\data\map_firedep_ca.paa";
		color[] = {0.764,0,0,0.8};
		size = 18;
		importance = "2 * 16 * 0.05";
		coefMin = 0.2;
		coefMax = 2;
	};
	class TouristSign
	{
		icon = "\dz\gear\navigation\data\map_tsign_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 1;
	};
	class Tourism
	{
		icon = "\dz\gear\navigation\data\map_tourism_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 2;
	};
	class Cross
	{
		icon = "\dz\gear\navigation\data\map_cross_ca.paa";
		size = 12;
		color[] = {1,1,1,0.9};
		importance = "0.7 * 16 * 0.05";
		coefMin = 0.1;
		coefMax = 1;
	};
	class Chapel
	{
		icon = "\dz\gear\navigation\data\map_chapel_ca.paa";
		color[] = {1,1,1,0.9};
		size = 12;
		importance = "1 * 16 * 0.05";
		coefMin = 0.9;
		coefMax = 3;
	};
	class Church
	{
		icon = "\dz\gear\navigation\data\map_church_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2 * 16 * 0.05";
		coefMin = 0.9;
		coefMax = 4;
	};
	class ViewTower
	{
		icon = "\dz\gear\navigation\data\map_viewtower_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2.5 * 16 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class TouristShelter
	{
		icon = "\dz\gear\navigation\data\map_tshelter_ca.paa";
		color[] = {1,1,1,0.9};
		size = 10;
		importance = "2 * 16 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class Quay
	{
		icon = "\dz\gear\navigation\data\map_quay_ca.paa";
		size = 16;
		color[] = {1,1,1,0.9};
		importance = "2 * 16 * 0.05";
		coefMin = 0.5;
		coefMax = 4;
	};
	class Bunker
	{
		icon = "\dz\gear\navigation\data\map_bunker_ca.paa";
		color[] = {1,1,1,0.9};
		size = 14;
		importance = "1.5 * 14 * 0.05";
		coefMin = 0.25;
		coefMax = 4;
	};
	class Fortress
	{
		icon = "\dz\gear\navigation\data\map_fortress_ca.paa";
		size = 16;
		color[] = {1,1,1,0.9};
		importance = "2 * 16 * 0.05";
		coefMin = 0.25;
		coefMax = 4;
	};
	class Rocks
	{
		icon = "\dz\gear\navigation\data\map_rock_ca.paa";
		color[] = {0.1,0.1,0.1,0.8};
		size = 12;
		importance = "0.5 * 12 * 0.05";
		coefMin = 0.25;
		coefMax = 4;
	};
	class Ruin
	{
		icon = "\dz\gear\navigation\data\map_ruin_ca.paa";
		size = 16;
		color[] = {1,1,1,0.9};
		importance = "1.2 * 16 * 0.05";
		coefMin = 1;
		coefMax = 4;
	};
};
