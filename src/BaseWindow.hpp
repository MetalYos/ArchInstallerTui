#pragma once

#include <iostream>
#include <curses.h>
#include <string>
#include <PubSub.hpp>

class BaseWindow {
public:
    BaseWindow(int id, PubSub& pubsub, const std::string& title);
    virtual ~BaseWindow() {}
    void SetPosition(int y, int x);
    void SetSize(int width, int height);
    void SetTitle(const std::string& title);
    int GetId() const;

    virtual void Show() {}
    virtual void Refresh();
    virtual void HandleInput(int c) {}

protected:
    void PrintInMiddle(WINDOW *win, int startY, int startX, int width, const std::string& str);

protected:
    int id;
    PubSub& pubsub;
    std::string title;
    int height, width, y, x;

    WINDOW* window;
};
