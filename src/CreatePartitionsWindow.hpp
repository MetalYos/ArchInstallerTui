#pragma once

#include <BaseWindow.hpp>
#include <Configuration.hpp>

// BaseWindow(int id, PubSub& pubsub, const std::string& title);

class CreatePartitionsWindow : public BaseWindow {
public:
    CreatePartitionsWindow(PubSub& PubSub);

    void Show() override;

private:
    void CheckBootMode();

private:
    EBootModes bootMode;
};
