#pragma once

#include <BaseWindow.hpp>
#include <Configuration.hpp>

class CreatePartitionsWindow : public BaseWindow {
private:

    void CheckBootMode();

private:
    EBootModes bootMode;
};
