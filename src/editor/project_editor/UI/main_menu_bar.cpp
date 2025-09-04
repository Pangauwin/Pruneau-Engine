#include "main_menu_bar.h"
#include <editor/io/filepicker.h>
#include <editor/project/project_manager.h>

#include <imgui/imgui.h>

bool display_main_menu_bar()
{
    if(!ImGui::BeginMainMenuBar())
    {
        ImGui::EndMainMenuBar();
        return true;
    } 

    if(ImGui::BeginMenu("File"))
    {
        if(ImGui::MenuItem("Open"))
        {
            std::vector<std::pair<std::wstring, std::wstring>> filters = {
                { L"Pruneau Project (*.pproject)", L"*.pproject" },
            };

            std::string _path = open_file_picker(filters);
            if (!_path.empty())
            {
                ProjectManager& project_manager = ProjectManager::getInstance();    
                project_manager.load_project(_path.c_str());
            }
        }
        ImGui::MenuItem("Save");
        ImGui::Spacing();
        ImGui::MenuItem("Create Project");

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Project"))
    {
        ImGui::MenuItem("Properties");
        ImGui::MenuItem("Preferences");

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    return true;
}