#include "render_window.h"

#include <imgui/imgui.h>

bool display_render_window()
{
    ImGui::SetNextWindowBgAlpha(1.f);

    ImGui::Begin("Render Window");

    ImGui::End();

    return true;
}