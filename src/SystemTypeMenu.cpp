#include <cstdlib>
#include <SystemTypeMenu.hpp>
#include <MenuDefs.hpp>

SystemTypeMenu::SystemTypeMenu(PubSub& pubsub, MenuPositions position)
    : BaseMenuClass(MENU_ID_SYSTEM_TYPE_MENU, pubsub, position, "System Type Menu") {
    choices.push_back({ "Laptop", MENU_ITEM_TYPE_RADIO, MENU_ID_NONE });
    choices.push_back({ "VmWare", MENU_ITEM_TYPE_RADIO, MENU_ID_NONE });
    choices.push_back({ "VirtualBox", MENU_ITEM_TYPE_RADIO, MENU_ID_NONE });
    choices.push_back({ "Back", MENU_ITEM_TYPE_NAV, MENU_ID_MAIN_MENU });

    isNavMenu = true;

    CreateMenu();
}

SystemTypeMenu::~SystemTypeMenu() {
    Destroy();
}

void SystemTypeMenu::Destroy() {
    // Unpost and free all the memory taken up
    unpost_menu(menu);
    free_menu(menu);
    for(int i = 0; i < choices.size(); ++i)
        free_item(items[i]);
}

