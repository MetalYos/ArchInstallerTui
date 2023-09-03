#include <BaseMenuClass.hpp>

BaseMenuClass::BaseMenuClass(int id, PubSub& pubsub, const std::string& title, MenuPositions position)
    : BaseWindow(id, pubsub, title), position(position)
{ 
    SetMenuPosition(position);
}

void BaseMenuClass::Show() {
    post_menu(menu);
    wrefresh(window);
}

void BaseMenuClass::Hide() {
    unpost_menu(menu);
    wrefresh(window);
}

void BaseMenuClass::HandleInput(int c) {
    switch(c) {
        case KEY_DOWN:
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(menu, REQ_UP_ITEM);
            break;
        case 10: {// Enter
            ITEM* currentItem = current_item(menu); 
            MenuItemChoice* menuItemChoice = static_cast<MenuItemChoice*>(item_userptr(currentItem));
            switch (menuItemChoice->type) {
                case (MENU_ITEM_TYPE_EXIT):
                    pubsub.Publish(EVENT_ID_EXIT_SELECTED);
                    break;
                case MENU_ITEM_TYPE_NAV:
                    Hide();
                    pubsub.Publish(EVENT_ID_NAV_MENU_SELECTED, &(menuItemChoice->navId));
                    break;
                default:
                    ItemSelected();
                    break;
            }
            break;
        }
    }
}

void BaseMenuClass::CreateMenu() {
    // Create Items
    items = (ITEM**)calloc(choices.size() + 1, sizeof(ITEM*));
    int i = 0; 
    for (; i < choices.size(); i++) {
        items[i] = new_item(choices[i].label.c_str(), "");
        set_item_userptr(items[i], (void*)&choices[i]);
    }
    items[i] = (ITEM *)NULL;

    // Create Menu
    menu = new_menu((ITEM**)items);

    // Create window
    window = newwin(height, width, y, x); 
    keypad(window, TRUE);

    // Set main window and sub window
    set_menu_win(menu, window);
    set_menu_sub(menu, derwin(window, 6, width - 2, 3, 1));

    // Set menu mark to a string " * "
    set_menu_mark(menu, " * ");

    // Print a border around the main window and print a title
    box(window, 0, 0);
	PrintInMiddle(window, 1, 0, width, title);
	mvwaddch(window, 2, 0, ACS_LTEE);
	mvwhline(window, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(window, 2, width - 1, ACS_RTEE);
	refresh(); 
}

void BaseMenuClass::SetMenuPosition(MenuPositions pos) {
    width = (int)(0.33f * COLS);
    height = (int)(0.5f * LINES);
    switch (pos) {
        case MENU_POS_CENTER:
            x = COLS / 2 - width / 2;
            y = LINES / 2 - height / 2;
            break;
        default:
            break;
    }
}

