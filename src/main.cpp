#include <curses.h>
#include <menu.h>
#include <iostream>
#include <MenuManager.hpp>

int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_RED, COLOR_BLACK);

    MenuManager::Instance().Initialize();
    MenuManager::Instance().Show();
    MenuManager::Instance().EventLoop();
    MenuManager::Instance().Destroy();

    endwin();
    return 0;
}
