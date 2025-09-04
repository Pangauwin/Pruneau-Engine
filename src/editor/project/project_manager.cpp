#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
#include "project_manager.h"

bool ProjectManager::load_project(const std::string& path) {
    std::string cleanPath = path;
    cleanPath += "\\project_settings.pproject";
    
    if (!cleanPath.empty() && cleanPath.front() == '"' && cleanPath.back() == '"') {
        cleanPath = cleanPath.substr(1, cleanPath.size() - 2);
    }

    std::ifstream file(cleanPath);
    if (!file.is_open()) {
        std::cerr << "Unable to open project : [" << cleanPath << "]" << std::endl;
        return false;
    }

    nlohmann::json _data;
    try {
        file >> _data;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON Error : " << e.what() << std::endl;
        return false;
    }

    if (current_project != nullptr) {
        delete current_project;
    }

    current_project = new Project;
    current_project->name = _data.value("name", "unamed project"); // default value if key missing
    current_project->asset_file_path = _data.value("asset_file_path", path + "\\assets_data.passet");
    current_project->editor_version = _data.value("editor_version", EDITOR_VERSION);

    std::cerr << "Project loaded : [" << cleanPath << "]" << std::endl;
    std::cerr << "Project name : [" << current_project->name << "]" << std::endl;
    std::cerr << "Project editor version : [" << current_project->editor_version << "]" << std::endl;

    return true;
}

bool ProjectManager::create_project(const char *path, const char *name)
{
    return false;
}

Project *ProjectManager::get_current_project()
{
    return current_project;
}
