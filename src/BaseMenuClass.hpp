#pragma once

#include <iostream>
#include <curses.h>
#include <menu.h>
#include <vector>
#include <string>
#include <BaseWindow.hpp>
#include <PubSub.hpp>
#include <WindowDefs.hpp>

class BaseMenuClass : public BaseWindow {
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
    BaseMenuClass(int id, PubSub& pubsub, const std::string& title, MenuPositions position);
    virtual ~BaseMenuClass() {}
    void Show() override;
    void Hide();
    virtual void HandleInput(int c) override;

protected:
    virtual void ItemSelected() {};
    void SetMenuPosition(MenuPositions pos);
    void CreateMenu();
    void PrintInMiddle(WINDOW *win, int startY, int startX, int width, const std::string& str);

protected:
    std::vector<MenuItemChoice> choices;
    MenuPositions position;

    ITEM** items;
    MENU* menu;
};
