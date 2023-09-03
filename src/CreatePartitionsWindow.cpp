#include <CreatePartitionsWindow.hpp>
#include <WindowDefs.hpp>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>

#define BOOT_MODE_FILE_PATH     "/sys/firmware/efi/fw_platform_size"
#define LIST_DISKS_PATH         "/sys/block"

namespace fs = std::filesystem;

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
    GetDisks();

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

void CreatePartitionsWindow::GetDisks() {
    // This structure would distinguish a file from a
    // directory
    struct stat sb;

    // Looping until all the items of the directory are
    // exhausted
    for (const auto& entry : fs::directory_iterator(LIST_DISKS_PATH)) {
        // Converting the path to const char * in the
        // subsequent lines
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.filename().string();

        // Testing whether the path points to a
        // non-directory or not, if it does, displays path
        if ((stat(outfilename_str.c_str(), &sb) != 0) || (sb.st_mode & S_IFDIR))
            disks.push_back(outfilename_str);
    }

    for (auto& disk : disks)
        printw("disk: %s\n", disk.c_str());
}

