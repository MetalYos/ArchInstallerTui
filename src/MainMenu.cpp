#include <cstdlib>
#include <MainMenu.hpp>
#include <MenuDefs.hpp>

MainMenu::MainMenu(PubSub& pubsub, MenuPositions position)
    : BaseMenuClass(MENU_ID_MAIN_MENU, pubsub, position, "Main Menu") {
    choices.push_back({ "System Type", MENU_ITEM_TYPE_NAV, MENU_ID_SYSTEM_TYPE_MENU });
    choices.push_back({ "Create Patitions", MENU_ITEM_TYPE_NAV, MENU_ID_NONE });
    choices.push_back({ "Enter User Info", MENU_ITEM_TYPE_NAV, MENU_ID_NONE });
    choices.push_back({ "Exit", MENU_ITEM_TYPE_EXIT, MENU_ID_NONE });

    isNavMenu = true;

    CreateMenu();
}

MainMenu::~MainMenu() {
    Destroy();
}

void MainMenu::Destroy() {
    // Unpost and free all the memory taken up
    unpost_menu(menu);
    free_menu(menu);
    for(int i = 0; i < choices.size(); ++i)
        free_item(items[i]);
}

