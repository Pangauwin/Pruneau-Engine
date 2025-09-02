#include "project.h"

class ProjectManager
{
public:

    static ProjectManager& getInstance()
    {
        static ProjectManager instance;
        return instance;
    }

    bool load_project(const std::string& path);
    bool create_project(const char* path, const char* name);

    Project* get_current_project();

    ProjectManager(const ProjectManager&) = delete;
    ProjectManager& operator=(const ProjectManager&) = delete;

private:
    ProjectManager() : current_project(nullptr) {} // private constructor = no "new ProjectManager()"
    Project* current_project;
};