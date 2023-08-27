#pragma once

#include <iostream>
#include <curses.h>
#include <menu.h>
#include <vector>
#include <string>
#include <PubSub.hpp>
#include <MenuDefs.hpp>

class BaseMenuClass {
public:
    enum MenuPositions {
        MENU_POS_TOP_LEFT = 0,
        MENU_POS_TOP_RIGHT,
        MENU_POS_TOP_CENTER,
        MENU_POS_BOTTOM_LEFT,
        MENU_POS_BOTTOM_RIGHT,
        MENU_POS_BOTTOM_CENTER,
        MENU_POS_LEFT,
        MENU_POS_RIGHT,
        MENU_POS_CENTER
    };

public:
    BaseMenuClass(int id, PubSub& pubsub, MenuPositions position, const std::string& title);
    virtual ~BaseMenuClass() {}
    void Show();
    void Hide();
    void Refresh();
    virtual void HandleInput(int c);

protected:
    virtual void ItemSelected() {};
    void SetMenuPosition(MenuPositions pos);
    void CreateMenu();
    void PrintInMiddle(WINDOW *win, int startY, int startX, int width, const std::string& str);

protected:
    int id;
    PubSub& pubsub;
    std::vector<MenuItemChoice> choices;
    MenuPositions position;
    std::string title;
    int height, width, y ,x;

    ITEM** items;
    MENU* menu;
    WINDOW* menuWindow;
};
