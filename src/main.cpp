#include <editor/editor.h>
#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char** argv)
{
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) // TODO: Move this into window.cpp file
    {
        std::cerr << "SDL Failed to initialize !" << std::endl;
        return -1;
    }

    switch (argc)
    {
        case 1:
        {
            launch_project_editor();
            break;   
        }
        case 2:
        {
            launch_project_editor(argv[1]);
            break;
        }
        default:
            std::cerr << "Pruneau does not support more than 1 argument" << std::endl;
            return -1;
    }   

    return 0;
}