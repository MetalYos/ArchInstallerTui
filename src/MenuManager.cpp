#include <MenuManager.hpp>
#include <MainMenu.hpp>
#include <SystemTypeMenu.hpp>

MenuManager::MenuManager()
    : pubsub(PubSub::Instance()), shouldExit(false)
{

}

void MenuManager::Initialize() {
    menus[MENU_ID_MAIN_MENU] = new MainMenu(
            pubsub,
            BaseMenuClass::MENU_POS_CENTER
        );  
    menus[MENU_ID_SYSTEM_TYPE_MENU] = new SystemTypeMenu(
            pubsub,
            BaseMenuClass::MENU_POS_CENTER
        );  

    menuStack.push_back(menus[MENU_ID_MAIN_MENU]);

    pubsub.Subscribe(EVENT_ID_EXIT_SELECTED, ExitSelectedEventHandler, this); 
    pubsub.Subscribe(EVENT_ID_NAV_MENU_SELECTED, NavMenuSelectedEventHandler, this); 
}

void MenuManager::Show() {
    menuStack.back()->Show();
}

void MenuManager::Refresh() {
    menuStack.back()->Refresh();
}

void MenuManager::EventLoop() {
    int c;
    while((c = getch()) != 'q') {
        menuStack.back()->HandleInput(c);
        Refresh();

        if (shouldExit)
            break;
    }
}

void MenuManager::Destroy() {
    for (auto pair : menus)
        delete pair.second;

    menus.clear();
    menuStack.clear();
}

void MenuManager::ExitSelectedEventHandler(void* args, void* eventData) {
    MenuManager* menuMgr = static_cast<MenuManager*>(args);
    menuMgr->shouldExit = true;
}

void MenuManager::NavMenuSelectedEventHandler(void* args, void* eventData) {
    MenuManager* menuMgr = static_cast<MenuManager*>(args);
    MenuIds navId = *static_cast<MenuIds*>(eventData);

    menuMgr->menuStack.pop_back();
    menuMgr->menuStack.push_back(menuMgr->menus[navId]);
    menuMgr->menuStack.back()->Show();
}

