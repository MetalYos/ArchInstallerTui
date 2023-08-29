#include <curses.h>
#include <iostream>
#include <TuiManager.hpp>

int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_RED, COLOR_BLACK);

    TuiManager::Instance().Initialize();
    TuiManager::Instance().Show();
    TuiManager::Instance().EventLoop();
    TuiManager::Instance().Destroy();

    endwin();
    return 0;
}
