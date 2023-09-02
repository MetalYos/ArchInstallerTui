#pragma once

enum ESystemTypes {
    SYSTEM_TYPE_LAPTOP = 0,
    SYSTEM_TYPE_VMWARE,
    SYSTEM_TYPE_VIRTUALBOX
};

enum EBootModes {
    BOOT_MODE_UEFI_64 = 0,
    BOOT_MODE_UEFI_32,
    BOOT_MODE_BIOS
};

struct Partition {
    int Id;
    int Offset;
    int Size;
    int Type;
};

struct Configuration {
    ESystemTypes systemType;
};
