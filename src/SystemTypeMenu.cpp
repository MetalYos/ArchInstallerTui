#include <cstdlib>
#include <SystemTypeMenu.hpp>
#include <WindowDefs.hpp>

SystemTypeMenu::SystemTypeMenu(PubSub& pubsub, MenuPositions position)
    : BaseMenuClass(WINDOW_ID_SYSTEM_TYPE_MENU, pubsub, "System Type Menu", position) {
    choices.push_back({ 0, "[x] Laptop", MENU_ITEM_TYPE_RADIO, WINDOW_ID_NONE });
    choices.push_back({ 1, "[ ] VmWare", MENU_ITEM_TYPE_RADIO, WINDOW_ID_NONE });
    choices.push_back({ 2, "[ ] VirtualBox", MENU_ITEM_TYPE_RADIO, WINDOW_ID_NONE });
    choices.push_back({ 3, "Back", MENU_ITEM_TYPE_NAV, WINDOW_ID_MAIN_MENU });

    selectedIndex = 0;

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

void SystemTypeMenu::ItemSelected() {
    ITEM* currentItem = current_item(menu);
    selectedIndex = item_index(currentItem);
    for (int i = 0; i < choices.size(); i++) {
        if (choices[i].label.c_str()[0] != '[')
            continue;

        if (i == selectedIndex)
            choices[i].label.replace(1, 1, "x");
        else
            choices[i].label.replace(1, 1, " ");

        set_current_item(menu, items[i]);
    }
    set_current_item(menu, currentItem);

    pubsub.Publish(EVENT_ID_SYSTEM_TYPE_SELECTED, (void*)&selectedIndex);
}

