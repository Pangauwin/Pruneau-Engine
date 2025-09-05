#include "project_editor.h"
#include "../project/project_manager.h"

#include <imgui/imgui.h>
#include <string>

#include "UI/main_menu_bar.h"
#include "UI/entity_viewer.h"
#include "UI/output.h"
#include "UI/inspector.h"
#include "UI/asset_browser.h"

#include <engine/app/app.h>

bool project_editor_init()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    app* _app = get_current_app();

    if(_app->m_params == NULL) return true; // if usage of the function empty(), it throw an exception with get scary (?)

    if(_app->m_params->find(APP_PARAM_TYPE_STRING) == _app->m_params->end()) return false; //TODO : cout a message that stand for saying we haven't found the path

    const char* _path = *(const char**)_app->m_params->find(APP_PARAM_TYPE_STRING)->second;

    ProjectManager& project_manager = ProjectManager::getInstance();    
    project_manager.load_project(_path);

    return true;
}

bool project_editor_update()
{
    if (!display_main_menu_bar()) return false;
    if (!display_entity_viewer()) return false;
    if (!display_output()) return false;
    if (!display_inspector()) return false;
    if (!display_asset_browser()) return false;

    return true;
}