#include <cstdlib>
#include <MainMenu.hpp>
#include <WindowDefs.hpp>

MainMenu::MainMenu(PubSub& pubsub, MenuPositions position)
    : BaseMenuClass(WINDOW_ID_MAIN_MENU, pubsub, "Main Menu", position) {
    choices.push_back({ 0, "System Type", MENU_ITEM_TYPE_NAV, WINDOW_ID_SYSTEM_TYPE_MENU });
    choices.push_back({ 1, "Create Patitions", MENU_ITEM_TYPE_NAV, WINDOW_ID_NONE });
    choices.push_back({ 2, "Enter User Info", MENU_ITEM_TYPE_NAV, WINDOW_ID_NONE });
    choices.push_back({ 3, "Exit", MENU_ITEM_TYPE_EXIT, WINDOW_ID_NONE });

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

