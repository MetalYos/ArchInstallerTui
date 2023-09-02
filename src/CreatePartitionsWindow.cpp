#include <CreatePartitionsWindow.hpp>
#include <fstream>
#include <string>

#define BOOT_MODE_FILE_PATH     "/sys/firmware/efi/fw_platform_size"

void CreatePartitionsWindow::CheckBootMode() {
    std::string line;
    std::ifstream platformSizeFile(BOOT_MODE_FILE_PATH);
    if (platformSizeFile.is_open()) {
        std::getline(platformSizeFile, line);
        if (line.find("64") != std::string::npos)
            bootMode = BOOT_MODE_UEFI_64;
        else if (line.find("32") != std::string::npos)
            bootMode = BOOT_MODE_UEFI_32;
        else
            bootMode = BOOT_MODE_BIOS;
    }
    else {
        bootMode = BOOT_MODE_BIOS;
    }
}
