#define SDL_MAIN_HANDLED

#include "SDL.h"
#include "glad/glad.h"
#include "Windowing/Window.h"
#include <iostream>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL init failed: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_GL_LoadLibrary(nullptr);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    GED_WINDOWING::Window window(
        "Engine Window",
        800, 600,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        true
    );

    SDL_GLContext context = SDL_GL_CreateContext(window.GetWindow());

    if (!context)
    {
        std::cout << "GL context failed: " << SDL_GetError() << "\n";
        return -1;
    }

    window.SetGLContext(context);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "GLAD failed\n";
        return -1;
    }

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        glViewport(0, 0, window.GetWidth(), window.GetHeight());

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window.GetWindow());
    }

    SDL_Quit();
    return 0;
}