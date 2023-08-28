#pragma once

enum ESystemType {
    SYSTEM_TYPE_LAPTOP = 0,
    SYSTEM_TYPE_VMWARE,
    SYSTEM_TYPE_VIRTUALBOX
};

struct Configuration {
    ESystemType systemType;
};
