#pragma once

#include <BaseWindow.hpp>
#include <Configuration.hpp>
#include <vector>
#include <string>

class CreatePartitionsWindow : public BaseWindow {
public:
    CreatePartitionsWindow(PubSub& PubSub);

    void Show() override;

private:
    void CheckBootMode();
    void GetDisks();

private:
    EBootModes bootMode;
    std::vector<std::string> disks;
};
