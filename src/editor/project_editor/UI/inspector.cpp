#include "inspector.h"

#include <imgui/imgui.h>

bool display_inspector()
{
    ImGui::SetNextWindowBgAlpha(.5f);

    ImGui::Begin("Inspector");

    ImGui::End();

    return true;
}