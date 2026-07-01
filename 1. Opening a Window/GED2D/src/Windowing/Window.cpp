#include "Windowing/Window.h"
#include <iostream>

namespace GED_WINDOWING
{

Window::Window(const std::string& title,
               int width,
               int height,
               int x,
               int y,
               bool v_sync,
               Uint32 flags)
    : m_Title(title),
      m_Width(width),
      m_Height(height),
      m_X(x),
      m_Y(y),
      m_Flags(flags)
{
    m_Window = SDL_CreateWindow(
        m_Title.c_str(),
        m_X, m_Y,
        m_Width, m_Height,
        m_Flags
    );

    if (!m_Window)
    {
        std::cout << "Failed to create window: " << SDL_GetError() << "\n";
    }

    if (v_sync)
    {
        SDL_GL_SetSwapInterval(1);
    }
}

Window::~Window()
{
    if (m_Context)
        SDL_GL_DeleteContext(m_Context);

    if (m_Window)
        SDL_DestroyWindow(m_Window);
}

SDL_Window* Window::GetWindow() const
{
    return m_Window;
}

SDL_GLContext Window::GetGLContext() const
{
    return m_Context;
}

void Window::SetGLContext(SDL_GLContext context)
{
    m_Context = context;
}

int Window::GetWidth() const
{
    return m_Width;
}

int Window::GetHeight() const
{
    return m_Height;
}

}
