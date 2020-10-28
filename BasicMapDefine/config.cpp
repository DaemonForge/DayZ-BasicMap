class CfgPatches
{
	class BasicMapDefine
	{
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};

class CfgMods
{
	class BasicMapDefine
	{
		dir="BasicMapDefine";
        name="BasicMap";
        type="mod";
	    dependencies[]={"GameLib", "Game", "World", "Mission"};
	    class defs
	    {
			class gameLibScriptModule
			{
				value = "";
				files[] = {
					"BasicMapDefine/scripts/Common"
					};
			};
			class gameScriptModule
            {
				value = "";
                files[]={
					"BasicMapDefine/scripts/Common"
					};
            };
			
			class worldScriptModule
            {
                value="";
                files[]={ 
					"BasicMapDefine/scripts/Common"
				};
            };
			
	        class missionScriptModule
            {
                value="";
                files[]={
					"BasicMapDefine/scripts/Common"
				};
            };
        };
    };
};