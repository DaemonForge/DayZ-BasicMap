class CfgPatches
{
	class BasicMapAirdropPlugin
	{
		requiredVersion = 0.1;
		requiredAddons[] = {
			"BasicMap"
		};
	};
};

class CfgMods
{
	class BasicMapAirdropPlugin
	{
		dir="AirdropPlugin";
        name="BasicMapAirdropPlugin";
        type="mod";
	    dependencies[]={"Game","World","Mission"};
	    class defs
	    {
			class gameScriptModule
            {
                value="";
                files[]={ 
					"AirdropPlugin/scripts/3_Game"
				};
            };
			class worldScriptModule
            {
                value="";
                files[]={ 
					"AirdropPlugin/scripts/4_World"
				};
            };
			class missionScriptModule
            {
                value="";
                files[]={ 
					"AirdropPlugin/scripts/5_Mission"
				};
            };
        };
    };
};