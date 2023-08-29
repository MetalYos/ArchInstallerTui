#pragma once

#include <BaseMenuClass.hpp>
#include <PubSub.hpp>

class SystemTypeMenu : public BaseMenuClass {
public:
    SystemTypeMenu(PubSub& pubsub, MenuPositions position);
    ~SystemTypeMenu();
    void Destroy();

protected:
    void ItemSelected() override;

protected:
    int selectedIndex;
};
