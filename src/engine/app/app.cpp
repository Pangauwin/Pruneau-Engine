#include "app.h"

#include <engine/renderer/renderer.h>
#include <SDL3/SDL_video.h>

static app* current_app = nullptr;

bool app_create(app *_app, const char *title, int width, int height, bool (*_init)(), bool (*_update)(), std::map<APP_PARAM_TYPE, void*>* _params)
{
    if (_app == nullptr) return false;

    SDL_memset(_app, 0, sizeof(app));
    _app->m_window = (window*)SDL_malloc(sizeof(window));

    if(!window_create(_app->m_window, title, width, height)) 
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Window creation failed !\n");
        return false;
    }

    _app->init = _init;
    _app->update = _update;
    _app->m_params = _params;

    current_app = _app;


    if(!_app->init()) 
    {
        SDL_Log("Not Hello there !");
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "App initialization failed !\n");
        return false;
    }

    _app->m_running = true;
    return true;
}

bool app_update(app* _app)
{
    window_update(_app->m_window);
    if(!_app->m_window->m_running) 
    {
        _app->m_running = false;
    }

    render_begin(_app->m_window->window_object);
    if(!_app->update())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "App update failed !\n");
    }
    render_end(_app->m_window->window_object);
    return true;
}

void app_destroy(app *_app)
{
    window_destroy(_app->m_window);
    delete _app->m_window;
}

app *get_current_app()
{
    return current_app;
}
