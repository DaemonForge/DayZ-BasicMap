modded class MissionBase extends MissionBaseWorld
{	
	override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            switch (id) {
                case BASICMAP_MENU:
                    menu = new BasicMapMenu;
                    break;
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}