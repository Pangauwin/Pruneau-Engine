#pragma once
#include <string>
#include <vector>
#include <Windows.h>

std::string open_file_picker(const std::vector<std::pair<std::wstring, std::wstring>>& filters, HWND owner = nullptr);

std::string open_folder_picker(HWND owner = nullptr);