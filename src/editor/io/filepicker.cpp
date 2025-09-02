#include "filepicker.h"

#define NOMINMAX

#include <Windows.h>
#include <commdlg.h>

std::string open_file_picker(const char* file_type_name, const char* file_type_extension)
{
    std::string filter = (std::string(file_type_name) + '\0' + std::string(file_type_extension) + '\0');
    filter.push_back('\0');

    char file_path[MAX_PATH] = "";
    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = filter.c_str();
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.lpstrFile = file_path;

    if(GetOpenFileNameA(&ofn)) return std::string(file_path);

    return "";
}