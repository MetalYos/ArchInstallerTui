#pragma once

#include <BaseMenuClass.hpp>
#include <PubSub.hpp>

class MainMenu : public BaseMenuClass {
public:
    MainMenu(PubSub& pubsub, MenuPositions position);
    ~MainMenu();
    void Destroy();

protected:
    void ItemSelected() override {}
};
