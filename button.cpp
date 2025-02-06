//
// Created by piotr on 05.02.25.
//

#include "button.h"
#include "thema.h"
#include "text.h"
#include "toolbox/all.h"
#include "helpers/draw.h"

namespace Witcher {
    using namespace bee;

    /****************************************************************
    *                                                               *
    *                 C T O R   w i t h   t e x t                   *
    *                                                               *
    ****************************************************************/

    Button::Button(std::string text, Widget* const parent) :
        Widget(ObjectType::Button, parent),
        text_{new Text(std::move(text), this)}
    {
        set_parent(parent);
        add_child(text_);
        set_visible(true);
        set_visible_frame(true);
        set_resizeable(true);
    }

    /****************************************************************
    *                                                               *
    *                       p r e p a r e                           *
    *                                                               *
    ****************************************************************/

    void Button::prepare() noexcept {
        for (const auto it : children()) {
            set_parent(this);
            it->prepare();
        }

        frame().resize(size_min());
        update_area(frame());
        text_->set_frame(area());
    }

    /****************************************************************
    *                                                               *
    *                       p r e p a r e                           *
    *                                                               *
    ****************************************************************/

    void Button::update_geometry() noexcept {
        // TODO: jeśli rozmiar przycisku większa od size_min() to trzeba wypośrodkować tekst
    }

    /****************************************************************
    *                                                               *
    *                    m o u s e _ d o w n                        *
    *                                                               *
    ****************************************************************/

    void Button::mouse_down(MouseEvent event) noexcept {
        if (focusable()) {
            set_focus(true);
            pressed_ = true;
        }
    }

    /****************************************************************
    *                                                               *
    *                    m o u s e _ u p                            *
    *                                                               *
    ****************************************************************/

    void Button::mouse_up(MouseEvent event) noexcept {
        if (focus()) {
            tickcounter_ = SDL_GetTicks();
        }
    }

    /****************************************************************
    *                                                               *
    *               m o u s e _ d o u b l e _ d o w n               *
    *                                                               *
    ****************************************************************/

    void Button::mouse_double_down(MouseEvent event) noexcept {
        if (focus()) {
            bee::box::print("Button::mouse_double_click\n");
        }
    }

    /****************************************************************
    *                                                               *
    *                m o u s e _ d o u b l e _ u p                  *
    *                                                               *
    ****************************************************************/

    void Button::mouse_double_up(MouseEvent event) noexcept {
    }


     /****************************************************************
    *                                                               *
    *                         u p d a t e                           *
    *                                                               *
    ****************************************************************/

    void Button::update() noexcept {
        if (tickcounter_)
            if (SDL_GetTicks() - tickcounter_.value() > 150) {
                pressed_ = !pressed_;
                tickcounter_.reset();
                if (focusable())
                    set_focus(pressed_);
            }
    }

    void Button::move_fixed(int const x, int const y) noexcept {
        box::println("Button::move_fixed ({}, {}): IN", x, y);
        set_fix_position(true);
        move(x, y);
        box::println("Button::move_fixed: OUT");
    }

    /****************************************************************
    *                                                               *
    *                           d r a w                             *
    *                                                               *
    ****************************************************************/

    void Button::draw() noexcept {
        update();
        if (!visible()) return;

        // Draw frame if needed.
        if (visible_frame()) {
            if (pressed_) {
                draw::fill_rect(renderer(), frame(), thema::DARK_3);
                draw::rect(renderer(), frame(), thema::BLUE_5);
            } else {
                draw::fill_rect(renderer(), frame(), thema::DEFAULT_WIDGET_BACKGROUND);
                draw::rect(renderer(), frame(), thema::DEFAULT_FRAME_COLOR);
            }
        }

        // Draw children.
        for (auto const child : children())
            child->draw();
    }

    Size Button::size_min() const noexcept {
        const auto [w, h] = text_->frame().size;
        return {
            .w = w + padding().left + padding().right,
            .h = h + padding().top + padding().bottom};
    }

    Size Button::size_max() const noexcept {
        const auto [w, h] = parent()->frame().size;
        return {.w = w - padding().left - padding().right, .h = h - padding().top - padding().bottom};
    }

}
