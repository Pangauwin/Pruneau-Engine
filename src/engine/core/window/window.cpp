#include "window.h"

bool window_create(window* _window, const char *title, int width, int height)
{
    const char* glsl_version = "#version 330";

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    
    //TODO : Load a conf file
    SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN;
    _window->window_object = SDL_CreateWindow(title, width, height, window_flags);
    
    if(_window->window_object == nullptr) 
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL window object failed to create : %s\n", SDL_GetError());
        return false;
    }

    _window->gl_context = SDL_GL_CreateContext(_window->window_object);

    if(_window->gl_context == nullptr) return false;

    SDL_GL_MakeCurrent(_window->window_object, _window->gl_context);

    // Enables VSync
    SDL_GL_SetSwapInterval(1); //TODO : pass this into a param in a .ini file

    SDL_SetWindowPosition(_window->window_object, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(_window->window_object);

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.IniFilename = nullptr;

    ImGui::StyleColorsDark();

    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;


    ImGui_ImplSDL3_InitForOpenGL(_window->window_object, _window->gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    _window->m_running = true;

    return true;
}

void window_update(window* _window)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        ImGui_ImplSDL3_ProcessEvent(&e);
        switch(e.type)
        {
            case SDL_EVENT_QUIT:
            {
                _window->m_running = false;
                break;
            }
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                if (e.window.windowID == SDL_GetWindowID(_window->window_object))
                {
                    _window->m_running = false;
                }
                break;
            }

            default:
                break;
        }
    }
}

void window_destroy(window *_window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(_window->gl_context);
    SDL_DestroyWindow(_window->window_object);
    
    SDL_Quit();
}
