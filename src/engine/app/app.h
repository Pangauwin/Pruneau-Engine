#pragma once

#include <engine/core/window/window.h>
#include <map>

enum APP_PARAM_TYPE 
{
    APP_PARAM_TYPE_STRING,
    APP_PARAM_TYPE_CHAR,
    APP_PARAM_TYPE_INT
};

struct app
{
    bool (*init)();
    bool (*update)();
    window* m_window;

    bool m_running;

    std::map<APP_PARAM_TYPE, void*>* m_params;
};

bool app_create(app* _app, const char* title, int width, int height, bool (*_init)(), bool (*_update)(), std::map<APP_PARAM_TYPE, void*>* _params);
bool app_update(app* _app);
void app_destroy(app* _app);

app* get_current_app();