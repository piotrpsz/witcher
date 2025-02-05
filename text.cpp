//
// Created by piotr on 05.02.25.
//

#include "text.h"
#include "thema.h"
#include "font_store.h"

namespace Witcher {

    Text::Text(std::string text, Widget* const parent) :
        Widget(ObjectType::Text, parent),
        text_(std::move(text))
    {
        set_parent(parent);
        set_renderer(parent->renderer());
        set_visible(true);
        set_visible_frame(true);    // for tests

        if (auto const font = FontStore::self().font("Mono-Regular", 10.5)) {
            if (auto rect = font->geometry(text_)) {
                auto&& [w, h] = *rect;
                set_area({0, 0, w, h});
                font_ = font;
                texture_ = font_->texture_for(renderer(), text_, thema::LIGHT_3);
            }
        }
    }

    Size Text::size_min() const noexcept {
        return frame().size;
    }
    Size Text::size_max() const noexcept {
        return frame().size;
    }

    void Text::update() noexcept {
    }

    void Text::draw() noexcept {
        if (visible()) {
            if (visible_frame()) {
                auto const [r, g, b, a] = thema::DEFAULT_FRAME_COLOR;
                SDL_SetRenderDrawColor(renderer(), r, g, b, a);
                auto const frect = frame().to_frect();
                SDL_RenderRect(renderer(), &frect);
            }
            auto const frect = area().to_frect();
            SDL_RenderTexture(renderer(), texture_, nullptr, &frect);
        }
    }

}
