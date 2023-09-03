#pragma once
#include <unordered_map>
#include <vector>
#include <PubSub.hpp>
#include <BaseWindow.hpp>
#include <WindowDefs.hpp>
#include <Configuration.hpp>

class TuiManager {
public:
    static TuiManager& Instance() {
        static TuiManager instance;
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
    static void SystemTypeSelectedEventHandler(void* args, void* eventData);

private:
    TuiManager();

private:
    std::unordered_map<WindowIds, BaseWindow*> windows;
    std::vector<BaseWindow*> windowStack;
    PubSub& pubsub;
    bool shouldExit;

    Configuration config;
};
