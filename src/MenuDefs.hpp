#pragma once

enum MenuIds {
    MENU_ID_NONE = 0,
    MENU_ID_MAIN_MENU,
    MENU_ID_SYSTEM_TYPE_MENU
};

enum MenuItemTypes {
    MENU_ITEM_TYPE_NONE = 0,
    MENU_ITEM_TYPE_EXIT,
    MENU_ITEM_TYPE_NAV,
    MENU_ITEM_TYPE_RADIO
};

struct MenuItemChoice {
    std::string label;
    int type; 
    int navId;
};

