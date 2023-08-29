#include <TuiManager.hpp>
#include <MainMenu.hpp>
#include <SystemTypeMenu.hpp>

TuiManager::TuiManager()
    : pubsub(PubSub::Instance()), shouldExit(false)
{

}

void TuiManager::Initialize() {
    windows[WINDOW_ID_MAIN_MENU] = new MainMenu(
            pubsub,
            BaseMenuClass::MENU_POS_CENTER
        );  
    windows[WINDOW_ID_SYSTEM_TYPE_MENU] = new SystemTypeMenu(
            pubsub,
            BaseMenuClass::MENU_POS_CENTER
        );  

    windowStack.push_back(windows[WINDOW_ID_MAIN_MENU]);

    pubsub.Subscribe(EVENT_ID_EXIT_SELECTED, ExitSelectedEventHandler, this); 
    pubsub.Subscribe(EVENT_ID_NAV_MENU_SELECTED, NavMenuSelectedEventHandler, this); 
    pubsub.Subscribe(EVENT_ID_SYSTEM_TYPE_SELECTED, SystemTypeSelectedEventHandler, this); 
}

void TuiManager::Show() {
    windowStack.back()->Show();
}

void TuiManager::Refresh() {
    windowStack.back()->Refresh();
}

void TuiManager::EventLoop() {
    int c;
    while((c = getch()) != 'q') {
        windowStack.back()->HandleInput(c);
        Refresh();

        if (shouldExit)
            break;
    }
}

void TuiManager::Destroy() {
    for (auto pair : windows)
        delete pair.second;

    windows.clear();
    windowStack.clear();
}

void TuiManager::ExitSelectedEventHandler(void* args, void* eventData) {
    TuiManager* mgr = static_cast<TuiManager*>(args);
    mgr->shouldExit = true;
}

void TuiManager::NavMenuSelectedEventHandler(void* args, void* eventData) {
    TuiManager* mgr = static_cast<TuiManager*>(args);
    WindowIds navId = *static_cast<WindowIds*>(eventData);

    mgr->windowStack.pop_back();
    mgr->windowStack.push_back(mgr->windows[navId]);
    mgr->windowStack.back()->Show();
}

void TuiManager::SystemTypeSelectedEventHandler(void* args, void* eventData) {
    TuiManager* mgr = static_cast<TuiManager*>(args);
    ESystemType type = *static_cast<ESystemType*>(eventData);

    mgr->config.systemType = type;
}

