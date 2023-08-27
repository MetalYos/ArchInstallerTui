#include <BaseMenuClass.hpp>

BaseMenuClass::BaseMenuClass(int id, PubSub& pubsub, MenuPositions position, const std::string& title)
    : id(id), pubsub(pubsub), position(position), title(title)
{ 
    SetMenuPosition(position);
}

void BaseMenuClass::Show() {
    post_menu(menu);
    wrefresh(menuWindow);
}

void BaseMenuClass::Hide() {
    unpost_menu(menu);
    wrefresh(menuWindow);
}

void BaseMenuClass::Refresh() {
    wrefresh(menuWindow);
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
    menuWindow = newwin(height, width, y, x); 
    keypad(menuWindow, TRUE);

    // Set main window and sub window
    set_menu_win(menu, menuWindow);
    set_menu_sub(menu, derwin(menuWindow, 6, width - 2, 3, 1));

    // Set menu mark to a string " * "
    set_menu_mark(menu, " * ");

    // Print a border around the main window and print a title
    box(menuWindow, 0, 0);
	PrintInMiddle(menuWindow, 1, 0, width, title);
	mvwaddch(menuWindow, 2, 0, ACS_LTEE);
	mvwhline(menuWindow, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(menuWindow, 2, width - 1, ACS_RTEE);
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

void BaseMenuClass::PrintInMiddle(WINDOW *win, int startY, int startX, int width, const std::string& str) {
    int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startX != 0)
		x = startX;
	if(startY != 0)
		y = startY;
	if(width == 0)
		width = 80;

	length = str.length();
	temp = (width - length)/ 2;
	x = startX + (int)temp;
	mvwprintw(win, y, x, "%s", str.c_str());
	refresh();
}

