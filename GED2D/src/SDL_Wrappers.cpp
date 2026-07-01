#include "SDL_Wrappers.h"
#include "SDL.h"

namespace GED_UTIL {

void SDL_Deleter::operator()(SDL_Window* window) const
{
    if (window)
        SDL_DestroyWindow(window);
}

void SDL_Deleter::operator()(SDL_GameController* controller) const
{
    if (controller)
        SDL_GameControllerClose(controller);
}

void SDL_Deleter::operator()(SDL_Cursor* cursor) const
{
    if (cursor)
        SDL_FreeCursor(cursor);
}

}