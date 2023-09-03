#pragma once

enum WindowIds {
    WINDOW_ID_NONE = 0,
    WINDOW_ID_MAIN_MENU,
    WINDOW_ID_SYSTEM_TYPE_MENU,
    WINDOW_ID_CREATE_PARTITIONS_WINDOW
};

enum MenuItemTypes {
    MENU_ITEM_TYPE_NONE = 0,
    MENU_ITEM_TYPE_EXIT,
    MENU_ITEM_TYPE_NAV,
    MENU_ITEM_TYPE_RADIO
};

struct MenuItemChoice {
    int pos;
    std::string label;
    int type; 
    int navId;
};

