#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_opengl3.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

struct window
{
    SDL_Window* window_object;
    SDL_GLContext gl_context;

    bool m_running;
};

bool window_create(window* _window, const char* title, int width, int height);
void window_update(window* _window);
void window_destroy(window* _window);