//
// Created by piotr on 26.02.25.
//

#pragma once
#include <string>
#include <SDL3/SDL_video.h>

namespace Witcher {
    class Dialog {
    public:
        static bool show(std::string const& title, std::string const& message, SDL_Window* window = nullptr) noexcept;
    };
}
