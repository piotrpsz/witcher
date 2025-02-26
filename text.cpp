//
// Created by piotr on 05.02.25.
//

#include "text.h"

#include <set>

#include "thema.h"
#include "font_store.h"
#include "toolbox/all.h"

namespace Witcher {

    Text::Text(std::string text,  Widget* const parent) :
        Widget(ObjectType::Text, parent),
        text_(std::move(text))
    {
        set_parent(parent);
        set_visible(true);
    }

    void Text::prepare() noexcept {
        if (colors.normal_foreground) {
            if (auto const font = FontStore::self().font("Mono-Regular", 10.5)) {
                if (auto rect = font->geometry(text_)) {
                    font_ = font;
                    texture_ = font_->texture_for(renderer(), text_, *colors.normal_foreground);
                    auto&& [w, h] = *rect;
                    set_frame({0, 0,w + padding().left + padding().right, h + padding().top + padding().bottom});
                }
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
