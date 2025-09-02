#include "entity_viewer.h"
#include <imgui/imgui.h>

bool display_entity_viewer()
{
    ImGui::SetNextWindowBgAlpha(.5f);

    ImGui::Begin("Entity viewer", (bool*) 0);

    ImGui::End();

    return true;
}