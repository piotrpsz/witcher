//
// Created by piotr on 05.02.25.
//
#pragma once

#include "../types.h"
#include "../toolbox/all.h"
#include <SDL3/SDL_render.h>

namespace Witcher::draw {
    inline void fill_rect(SDL_Renderer* const renderer, Rect const rect, SDL_Color const color) noexcept {
        auto const [r, g, b, a] = color;
        if (SDL_SetRenderDrawColor(renderer, r, g, b, a)) {
            const auto frect = rect.to_frect();
            if (SDL_RenderFillRect(renderer, &frect))
                return;
        }
        bee::box::println_error("{}", SDL_GetError());
    }

    inline void rect(SDL_Renderer* const renderer, Rect const rect, SDL_Color const color) noexcept {
        auto [r, g, b, a] = color;
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        const auto frect = rect.to_frect();
        SDL_RenderRect(renderer, &frect);
    }
}
