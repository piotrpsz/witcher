//
// Created by piotr on 05.02.25.
//

#pragma once

#include "widgets/widget/widget.h"
#include "thema.h"
#include "types.h"
#include <string_view>
#include <memory>
#include <SDL3/SDL_render.h>

namespace Witcher {
    class Font;

    class Text final : public Widget {
        std::string text_;
        std::shared_ptr<Font> font_;
        SDL_Texture* texture_{};
    public:
        explicit Text(std::string text, Widget* parent = nullptr);

        [[nodiscard]] std::string text() const noexcept { return text_; }

        void set_color(SDL_Color const color) noexcept {
            colors.normal_foreground = color;
        }
        void update() noexcept override;
        void draw() noexcept override;
        [[nodiscard]] Size size_min() const noexcept override;
        [[nodiscard]] Size size_max() const noexcept override;
        void update_geometry() noexcept override {}
        void prepare() noexcept override;
    };
}