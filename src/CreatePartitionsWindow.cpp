#include <CreatePartitionsWindow.hpp>
#include <WindowDefs.hpp>
#include <fstream>
#include <string>

#define BOOT_MODE_FILE_PATH     "/sys/firmware/efi/fw_platform_size"

CreatePartitionsWindow::CreatePartitionsWindow(PubSub& PubSub) 
    : BaseWindow(WINDOW_ID_CREATE_PARTITIONS_WINDOW, pubsub, "Create Partitions")
{

    width = (int)(0.33f * COLS);
    height = (int)(0.5f * LINES);
    x = COLS / 2 - width / 2;
    y = LINES / 2 - height / 2;
    window = newwin(height, width, y, x); 

    // Print a border around the main window and print a title
    box(window, 0, 0);
	PrintInMiddle(window, 1, 0, width, title);
	mvwaddch(window, 2, 0, ACS_LTEE);
	mvwhline(window, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(window, 2, width - 1, ACS_RTEE);
    
    CheckBootMode();

    printw("BootMode: %d\n", bootMode);
	refresh(); 
}

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

void CreatePartitionsWindow::Show() {
    wrefresh(window);
}

