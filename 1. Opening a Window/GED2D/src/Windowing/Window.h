#pragma once

#include "SDL.h"
#include "glad/glad.h"
#include <string>
#include <memory>

namespace GED_WINDOWING
{

class Window
{
public:
    Window(const std::string& title,
           int width,
           int height,
           int x,
           int y,
           bool v_sync = true,
           Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    ~Window();

    SDL_Window* GetWindow() const;

    SDL_GLContext GetGLContext() const;
    void SetGLContext(SDL_GLContext context);

    int GetWidth() const;
    int GetHeight() const;

private:
    SDL_Window* m_Window = nullptr;
    SDL_GLContext m_Context = nullptr;

    std::string m_Title;
    int m_Width = 0;
    int m_Height = 0;
    int m_X = 0;
    int m_Y = 0;
    Uint32 m_Flags = 0;
};

}