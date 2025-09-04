#include "filepicker.h"

#include <shobjidl.h>
#include <string>
#include <vector>

std::string open_file_picker(
    const std::vector<std::pair<std::wstring, std::wstring>>& filters, // {description, pattern}
    HWND owner)
{
    // Initialize COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) return "";

    IFileDialog* pfd = nullptr;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pfd));
    if (FAILED(hr)) {
        CoUninitialize();
        return "";
    }

    // Build filter list
    std::vector<COMDLG_FILTERSPEC> specs;
    specs.reserve(filters.size());
    for (auto& f : filters) {
        specs.push_back({ f.first.c_str(), f.second.c_str() });
    }

    if (!specs.empty()) {
        pfd->SetFileTypes((UINT)specs.size(), specs.data());
        pfd->SetFileTypeIndex(1); // Default index (starts with 1)
    }

    // Options
    DWORD options;
    pfd->GetOptions(&options);
    pfd->SetOptions(options | FOS_FILEMUSTEXIST | FOS_PATHMUSTEXIST);

    hr = pfd->Show(owner);
    if (FAILED(hr)) {
        pfd->Release();
        CoUninitialize();
        return ""; // TODO : return an error here
    }

    // Get results
    IShellItem* psi = nullptr;
    hr = pfd->GetResult(&psi);
    if (FAILED(hr)) {
        pfd->Release();
        CoUninitialize();
        return ""; // TODO : return an error here
    }

    PWSTR pszFilePath = nullptr;
    hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

    std::string result;
    if (SUCCEEDED(hr) && pszFilePath) {
        char buffer[MAX_PATH];
        WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, buffer, MAX_PATH, NULL, NULL);
        result = buffer;
        CoTaskMemFree(pszFilePath);
    }

    psi->Release();
    pfd->Release();
    CoUninitialize();

    return result;
}

std::string open_folder_picker(HWND owner)
{
    // Initialize COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) return "";

    IFileDialog* pfd = nullptr;

    // Create Dialog box
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pfd));
    if (FAILED(hr)) {
        CoUninitialize();
        return ""; // TODO : return an error here
    }

    DWORD options;
    pfd->GetOptions(&options);
    pfd->SetOptions(options | FOS_PICKFOLDERS);

    // Show the dialog
    hr = pfd->Show(owner);
    if (FAILED(hr)) {
        pfd->Release();
        CoUninitialize();
        return ""; // TODO : return an error here
    }

    // Get Result
    IShellItem* psi = nullptr;
    hr = pfd->GetResult(&psi);
    if (FAILED(hr)) {
        pfd->Release();
        CoUninitialize();
        return ""; // TODO : return an error here
    }

    PWSTR pszFilePath = nullptr;
    hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

    std::string result;
    if (SUCCEEDED(hr) && pszFilePath) {
        // Convert wide string to std::string (UTF-8)
        char buffer[MAX_PATH];
        WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, buffer, MAX_PATH, NULL, NULL);
        result = buffer;
        CoTaskMemFree(pszFilePath);
    }

    psi->Release();
    pfd->Release();
    CoUninitialize();

    return result;
}
