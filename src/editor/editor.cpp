#include <editor/editor.h>
#include <engine/app/app.h>
#include <editor/project_editor/project_editor.h>

void launch_project_editor(char *_path)
{
    app* editor_app = new app;

    std::map<APP_PARAM_TYPE, void*> app_params{
        {APP_PARAM_TYPE_STRING, &_path}             // Open Project
    };

    app_create(editor_app, "Pruneau's game engine editor", PROJECT_EDITOR_WIDTH, PROJECT_EDITOR_HEIGHT, project_editor_init, project_editor_update, &app_params);

    while(editor_app->m_running)
    {
        app_update(editor_app);
    }

    app_destroy(editor_app);
    delete editor_app;
}

void launch_project_editor()
{
    app* editor_app = new app;

    app_create(editor_app, "Pruneau's game engine editor", PROJECT_EDITOR_WIDTH, PROJECT_EDITOR_HEIGHT, project_editor_init, project_editor_update, nullptr);

    while(editor_app->m_running)
    {
        app_update(editor_app);
    }

    app_destroy(editor_app);
    delete editor_app;
}