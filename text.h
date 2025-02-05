//
// Created by piotr on 05.02.25.
//

#pragma once

#include "widget.h"
#include <string>
#include <memory>
#include <SDL3/SDL_render.h>

namespace Witcher {
    class Font;

    class Text final : public Widget {
        std::string text_;
        std::shared_ptr<Font> font_;
        SDL_Texture* texture_;
    public:
        explicit Text(std::string text, Widget* parent = nullptr);

        void update() noexcept override;
        void draw() noexcept override;
        [[nodiscard]] Size size_min() const noexcept override;
        [[nodiscard]] Size size_max() const noexcept override;
    };
}