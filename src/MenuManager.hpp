#pragma once
#include <unordered_map>
#include <vector>
#include <PubSub.hpp>
#include <BaseMenuClass.hpp>
#include <MenuDefs.hpp>

class MenuManager {
public:
    static MenuManager& Instance() {
        static MenuManager instance;
        return instance;
    }

    void Initialize();
    void Show();
    void Refresh();
    void EventLoop();
    void Destroy();

    // Event Handlers
    static void ExitSelectedEventHandler(void* args, void* eventData);
    static void NavMenuSelectedEventHandler(void* args, void* eventData);

private:
    MenuManager();

private:
    std::unordered_map<MenuIds, BaseMenuClass*> menus;
    std::vector<BaseMenuClass*> menuStack;
    PubSub& pubsub;
    bool shouldExit;
};
