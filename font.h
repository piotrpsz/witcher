//
// Created by piotr on 03.02.25.
//

#pragma once

#include "types.h"
#include <string_view>
#include <vector>
#include <memory>
#include <optional>
#include <cmath>
#include <SDL3_ttf/SDL_ttf.h>

namespace Witcher {
    class Font final {
        std::string name_{};
        f32 size_{};
        TTF_Font* font_{};
    public:
        Font(std::string_view name, f32 size);
        ~Font();

    };
}
