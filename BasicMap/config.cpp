class CfgPatches
{
	class BasicMap
	{
		requiredVersion = 0.1;
		requiredAddons[] = {
			"BasicMapDefine", 
			"DZ_Worlds_Chernarusplus_World",
			"DZ_Gear_Navigation",
			"DZ_Data",
			"DZ_Scripts"
		};
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
        type = "Mod";
		inputs = "BasicMap/data/Inputs.xml";
	    dependencies[]={"Game", "World", "Mission"};
	    class defs
	    {
			class gameScriptModule
            {
				value = "";
                files[]={
					"BasicMap/scripts/3_Game"
					};
            };
			
			class worldScriptModule
            {
                value="";
                files[]={ 
					"BasicMap/scripts/4_World" 
				};
            };
			
	        class missionScriptModule
            {
                value="";
                files[]={
					"BasicMap/scripts/5_Mission" 
				};
            };
        };
    };
	
	
};

class CfgVehicles
{
	class Inventory_Base;
	class BM_Navigator: Inventory_Base
	{
		scope = 2;
		displayName = "Navigator";
		descriptionShort = "A Navigator GPS Unit to help you find your way";
		model = "BasicMap\data\Navigator\Navigator.p3d";
		itemSize[] = {1,3};
		weight = 950;
		absorbency = 0.5;
		rotationFlags = 1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 125;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
		attachments[] = {"BatteryD"};
		inventorySlot[] = {"WalkieTalkie"};
		repairableWithKits[] = {7};
		repairCosts[] = {25.0};
		class EnergyManager
		{
			hasIcon = 1;
			autoSwitchOffWhenInCargo = 0;
			energyUsagePerSecond = 0.008;
			plugType = 1;
			attachmentAction = 1;
			updateInterval = 40;
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
				name = "Camp Shkolnik";
			};
			class Camp_Pobeda
			{
				name = "Camp Pobeda";
			};
			class Camp_Metalurg
			{
				name = "Camp Metalurg";
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
				name = "Mutnyi Bay";
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
				name = "Medvezhi Lugi";
			};
			class Ruin_Voron
			{
				name = "Voron Castle";
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
				name = "VERESNIK MILITARY CAMP(VMC)";
				type = "MilitaryBase";
			};
			class Local_MB_Tisy
			{
				name = "TISY MILITARY BASE";
				type = "MilitaryBase";
			};
			class Local_MB_Kamensk
			{
				name = "KAMENSK MILITARY BASE";
				type = "MilitaryBase";
			};
			class Local_MB_Zeleno
			{
				name = "ZELENOGORSK MILITARY BASE";
				type = "MilitaryBase";
			};
			class Local_MB_Pavlovo
			{
				name = "PAVLOVO MILITARY BASE";
				type = "MilitaryBase";
			};
			class Local_AF_Balota
			{
				name = "BALOTA AIRFIELD";
				type = "MilitaryBase";
			};
			class Local_AF_Krasno
			{
				name = "KRASNO AIRFIELD";
				type = "MilitaryBase";
			};
			class Local_AF_Vybor
			{
				name = "VYBOR AIRFIELD";
				type = "MilitaryBase";
			};
			
			//Custom added Military Locations
			class Local_Custom_MIL_Berezino
			{
				name = "BEREZINO OUTPOST";
				position[] = {11963.87,9132.43};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_NovyLug
			{
				name = "NOVY LUG CHECKPOINT";
				position[] = {9581.39,11796.36};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Elektrozavodsk
			{
				name = "ELEKTROZAVODSK OUTPOST";
				position[] = {10480.1,2354.87};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Turovo
			{
				name = "TUROVO OUTPOST";
				position[] = {13623.9,13736.24};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_StarySobor
			{
				name = "STARY SOBOR MILITARY BASE";
				position[] = {6353.17, 7793.61};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Sosnovy
			{
				name = "SOSNOVY Checkpoint";
				position[] = {2719.05, 6756.86};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Ostry
			{
				name = "OSTRY OUTPOST";
				position[] = {10955.64,13341.25};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Severograd
			{
				name = "SEVEROGRAD CHECKPOINT";
				position[] = {7071.42,12735.87};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Arsenovo
			{
				name = "ARSENOVO CHECKPOINT";
				position[] = {8562.08, 14000.54};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Grozovy
			{
				name = "GROZOVY CHECKPOINT";
				position[] = {3655.72,14921.88};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Zaprudnoye
			{
				name = "ZAPRUDNOYE CHECKPOINT";
				position[] = {4967.62,12910.81};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Bashnya
			{
				name = "BASHNYA MILITARY BASE";
				position[] = {4100.3,11680.26};
				type = "MilitaryBase";
			};
			class Local_Custom_MIL_TriKresta
			{
				name = "TRI-KRESTA CHECKPOINT";
				position[] = {324.01,9323.51};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Tikhiyzaliv
			{
				name = "TIKHIYZALIV CHECKPOINT";
				position[] = {780.37,1870.99};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Chernogorsk
			{
				name = "CHERNOGORSK MILITARY BASE";
				position[] = {7259.27,3023.44};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Novoselki
			{
				name = "NOVOSELKI CHECKPOINT";
				position[] = {5822.97,3079.82};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Topolka
			{
				name = "TOPOLKA CHECKPOINT";
				position[] = {10240.12,4031.73};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Staroye
			{
				name = "STAROYE OUTPOST";
				position[] = {10444.62,5969.2};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Gorka
			{
				name = "GORKA CHECKPOINT";
				position[] = {10473.13,9167.24};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Myshkino
			{
				name = "MYSHKINO MILITARY BASE";
				position[] = {1192.99,7236.72};
				type = "MilitaryOutpost";
			};
			class Local_Custom_MIL_Balota
			{
				name = "BUNKER BALOTA";
				position[] = {5167.10, 2388.16};
				type = "MilitaryOutpost";
			};
			class Local_Chernogorsk_rus
			{
				name = "Черногорск";
				position[] = {6778.619,2230};
				type = "RussianNameCity";
			};
			class Local_Novodmitrovsk_rus
			{
				name = "Новодмитровск";
				position[] = {11324.77,14290};
				type = "RussianNameCity";
			};
			class Local_Novoselki_rus
			{
				name = "Новоселки";
				position[] = {6115.91,3216.36};
				type = "RussianName";
			};
			class Local_Dubovo_rus
			{
				name = "Дубово";
				position[] = {6754.51,3555.257};
				type = "RussianName";
			};
			class Local_Vysotovo_rus
			{
				name = "Высотово";
				position[] = {5701.24,2516.11};
				type = "RussianName";
			};
			class Local_Zelenogorsk_rus
			{
				name = "Зеленогорск";
				position[] = {2796,5080};
				type = "RussianNameCity";
			};
			class Local_Berezino_rus
			{
				name = "Березино";
				position[] = {12362.383,9670};
				type = "RussianNameCity";
			};
			class Local_Elektrozavodsk_rus
			{
				name = "Электрозаводск";
				position[] = {10276.68,1900};
				type = "RussianNameCity";
			};
			class Local_NovayaPetrovka_rus
			{
				name = "Новая Петровка";
				position[] = {3477.169,12840};
				type = "RussianNameCity";
			};
			class Local_Gorka_rus
			{
				name = "Горка";
				position[] = {9524,8910};
				type = "RussianName";
			};
			class Local_Solnechny_rus
			{
				name = "Солнечный";
				position[] = {13487.724,6180};
				type = "RussianName";
			};
			class Local_StarySobor_rus
			{
				name = "Старый Собор";
				position[] = {6114,7810};
				type = "RussianName";
			};
			class Local_Vybor_rus
			{
				name = "Выбор";
				position[] = {3909.831,8970};
				type = "RussianName";
			};
			class Local_Severograd_rus
			{
				name = "Североград";
				position[] = {8168.484,12480};
				type = "RussianNameCity";
			};
			class Local_Bor_rus
			{
				name = "Бор";
				position[] = {3316.406,4030};
				type = "RussianName";
			};
			class Local_Svetloyarsk_rus
			{
				name = "Светлоярск";
				position[] = {13989.74,13220};
				type = "RussianName";
			};
			class Local_Krasnostav_rus
			{
				name = "Красностав";
				position[] = {11203.167,12300};
				type = "RussianName";
			};
			class Local_ChernayaPolyana_rus
			{
				name = "Черная Поляна";
				position[] = {12158.54,13730};
				type = "RussianName";
			};
			class Local_Polyana_rus
			{
				name = "Поляна";
				position[] = {10794,8120};
				type = "RussianName";
			};
			class Local_Tulga_rus
			{
				name = "Тулга";
				position[] = {12768,4340};
				type = "RussianName";
			};
			class Local_Msta_rus
			{
				name = "Мста";
				position[] = {11333.79,5380};
				type = "RussianName";
			};
			class Local_Staroye_rus
			{
				name = "Старое";
				position[] = {10212.52,5340};
				type = "RussianName";
			};
			class Local_Shakhovka_rus
			{
				name = "Шаковка";
				position[] = {9728.64,6520};
				type = "RussianName";
			};
			class Local_Dolina_rus
			{
				name = "Долина";
				position[] = {11285.17,6590};
				type = "RussianName";
			};
			class Local_Orlovets_rus
			{
				name = "Орловец";
				position[] = {12250,7210};
				type = "RussianName";
			};
			class Local_NovySobor_rus
			{
				name = "Новый Собор";
				position[] = {7123.63,7730};
				type = "RussianName";
			};
			class Local_Kabanino_rus
			{
				name = "Кабанино";
				position[] = {5300.71,8600};
				type = "RussianName";
			};
			class Local_Mogilevka_rus
			{
				name = "Могилевка";
				position[] = {7650.41,5050};
				type = "RussianName";
			};
			class Local_Nadezhdino_rus
			{
				name = "Надеждино";
				position[] = {5894,4740};
				type = "RussianName";
			};
			class Local_Guglovo_rus
			{
				name = "Гуглово";
				position[] = {8445,6530};
				type = "RussianName";
			};
			class Local_Kamyshovo_rus
			{
				name = "Камышово";
				position[] = {12170,3410};
				type = "RussianName";
			};
			class Local_Pusta_rus
			{
				name = "Пуста";
				position[] = {9197,3830};
				type = "RussianName";
			};
			class Local_Dubrovka_rus
			{
				name = "Дубровка";
				position[] = {10324.299,9840};
				type = "RussianName";
			};
			class Local_VyshnayaDubrovka_rus
			{
				name = "Верхняя Дубровка";
				position[] = {9926.823,10420};
				type = "RussianName";
			};
			class Local_Khelm_rus
			{
				name = "Хелм";
				position[] = {12329.27,10730};
				type = "RussianName";
			};
			class Local_Olsha_rus
			{
				name = "Ольша";
				position[] = {13402,12850};
				type = "RussianName";
			};
			class Local_Gvozdno_rus
			{
				name = "Гвоздно";
				position[] = {8644.751,11890};
				type = "RussianName";
			};
			class Local_Grishino_rus
			{
				name = "Гришино";
				position[] = {5980,10210};
				type = "RussianName";
			};
			class Local_Rogovo_rus
			{
				name = "Рогово";
				position[] = {4802,6700};
				type = "RussianName";
			};
			class Local_Pogorevka_rus
			{
				name = "Погоревка";
				position[] = {4445,6280};
				type = "RussianName";
			};
			class Local_Pustoshka_rus
			{
				name = "Пустошка";
				position[] = {3137.944,7850};
				type = "RussianName";
			};
			class Local_Kozlovka_rus
			{
				name = "Козловка";
				position[] = {4402,4690};
				type = "RussianName";
			};
			class Local_Karmanovka_rus
			{
				name = "Кармановка";
				position[] = {12700.628,14650};
				type = "RussianName";
			};
			class Local_Balota_rus
			{
				name = "Балота";
				position[] = {4527.58,2420};
				type = "RussianName";
			};
			class Local_Komarovo_rus
			{
				name = "Комарово";
				position[] = {3702,2400};
				type = "RussianName";
			};
			class Local_Kamenka_rus
			{
				name = "Каменка";
				position[] = {1981,2160};
				type = "RussianName";
			};
			class Local_Myshkino_rus
			{
				name = "Мышкино";
				position[] = {2048,7220};
				type = "RussianName";
			};
			class Local_Pavlovo_rus
			{
				name = "Павлово";
				position[] = {1693.98,3810};
				type = "RussianName";
			};
			class Local_Lopatino_rus
			{
				name = "Лопатино";
				position[] = {2801,9990};
				type = "RussianName";
			};
			class Local_Vyshnoye_rus
			{
				name = "Вышное";
				position[] = {6629,6010};
				type = "RussianName";
			};
			class Local_Prigorodki_rus
			{
				name = "Пригородки";
				position[] = {7760,3290};
				type = "RussianName";
			};
			class Local_Drozhino_rus
			{
				name = "Дрожжино";
				position[] = {3374,4820};
				type = "RussianName";
			};
			class Local_Sosnovka_rus
			{
				name = "Сосновка";
				position[] = {2556,6160};
				type = "RussianName";
			};
			class Local_Nizhneye_rus
			{
				name = "Нижнее";
				position[] = {12824.88,8050};
				type = "RussianName";
			};
			class Local_Pulkovo_rus
			{
				name = "Пулково";
				position[] = {5015,5560};
				type = "RussianName";
			};
			class Local_Berezhki_rus
			{
				name = "Бережки";
				position[] = {15020,13860};
				type = "RussianName";
			};
			class Local_Turovo_rus
			{
				name = "Турово";
				position[] = {13630,14110};
				type = "RussianName";
			};
			class Local_BelayaPolyana_rus
			{
				name = "Белая Поляна";
				position[] = {14166,14920};
				type = "RussianName";
			};
			class Local_Dobroye_rus
			{
				name = "Доброе";
				position[] = {12996,15020};
				type = "RussianName";
			};
			class Local_Nagornoye_rus
			{
				name = "Нагорное";
				position[] = {9286,14630};
				type = "RussianName";
			};
			class Local_Svergino_rus
			{
				name = "Свергино";
				position[] = {9493.52,13830};
				type = "RussianName";
			};
			class Local_Ratnoye_rus
			{
				name = "Ратное";
				position[] = {6195.878,12720};
				type = "RussianName";
			};
			class Local_Kamensk_rus
			{
				name = "Каменск";
				position[] = {6748.741,14390};
				type = "RussianName";
			};
			class Local_Krasnoye_rus
			{
				name = "Красное";
				position[] = {6411.374,14980};
				type = "RussianName";
			};
			class Local_StaryYar_rus
			{
				name = "Старый Яр";
				position[] = {4987.86,14950};
				type = "RussianName";
			};
			class Local_Polesovo_rus
			{
				name = "Полесово";
				position[] = {5955.737,13510};
				type = "RussianName";
			};
			class Local_Tisy_rus
			{
				name = "Тисы";
				position[] = {3441.65,14750};
				type = "RussianName";
			};
			class Local_Topolniki_rus
			{
				name = "Топольники";
				position[] = {2913.745,12320};
				type = "RussianName";
			};
			class Local_Zaprudnoye_rus
			{
				name = "Запрудное";
				position[] = {5214,12750};
				type = "RussianName";
			};
			class Local_Sinystok_rus
			{
				name = "Синысток";
				position[] = {1538.278,11860};
				type = "RussianName";
			};
			class Local_Vavilovo_rus
			{
				name = "Вавилово";
				position[] = {2260,11060};
				type = "RussianName";
			};
			class Local_Kumyrna_rus
			{
				name = "Кумырна";
				position[] = {8297,6000};
				type = "RussianName";
			};
			class Local_Kalinovka_rus
			{
				name = "Калиновка";
				position[] = {7445,13360};
				type = "RussianName";
			};
			class Local_Bogatyrka_rus
			{
				name = "Богатырка";
				position[] = {1453.62,8830.92};
				type = "RussianName";
			};
			class Local_Zvir_rus
			{
				name = "Звир";
				position[] = {574.33,5270.42};
				type = "RussianName";
			};
			class Local_Zabolotye_rus
			{
				name = "Заболотье";
				position[] = {1253.859,9930.26};
				type = "RussianName";
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
	class RussianName: Name
	{
		color[] = {0.272, 0.759, 0.951,1};
		textSize = 0.052;
		importance = 4;
	};
	class RussianNameCity: Name
	{
		color[] = {0.272, 0.759, 0.951,1};
		textSize = 0.065;
		importance = 6;
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

