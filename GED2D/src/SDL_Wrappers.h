#pragma once

#include "SDL.h"
#include <memory>

namespace GED_UTIL {

struct SDL_Deleter {
    void operator()(SDL_Window* window) const;
    void operator()(SDL_GameController* controller) const;
    void operator()(SDL_Cursor* cursor) const;
};

using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
using Controller = std::shared_ptr<SDL_GameController>;
using Cursor = std::shared_ptr<SDL_Cursor>;

}