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
        TTF_Font* font_{};
        std::string name_;
        f32 size_;
    public:
        Font(std::string_view name, f32 size);
        ~Font() = default;

        [[nodiscard]] std::string_view name() const noexcept { return name_; };
        [[nodiscard]] f32 size() const noexcept { return size_; };

        [[nodiscard]] bool valid() const noexcept { return font_ != nullptr; }
        void description() const noexcept;
        [[nodiscard]] std::optional<Size> geometry(std::string const& text) const noexcept;
        SDL_Texture* texture_for(SDL_Renderer* renderer, std::string const& text, SDL_Color color) const noexcept;

    private:
        static std::string style(TTF_FontStyleFlags flags) noexcept;
        static std::string alignment(TTF_HorizontalAlignment flags) noexcept;
    };
}
