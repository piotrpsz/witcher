//
// Created by piotr on 05.02.25.
//

#include "button.h"
#include "thema.h"
#include "text.h"
#include "toolbox/all.h"
#include "helpers/draw.h"

namespace Witcher {
    /****************************************************************
    *                                                               *
    *                 C T O R   w i t h   t e x t                   *
    *                                                               *
    ****************************************************************/

    Button::Button(std::string text, Widget* const parent) :
        Widget(ObjectType::Button, parent)
    {
        if (parent) {
            set_parent(parent);
            set_renderer(parent->renderer());
        }
        set_visible(true);
        set_visible_frame(true);
        set_resizeable(true);

        auto const child = new Text(std::move(text), this);
        {
            const auto [w, h] = child->frame().size;
            set_frame({0, 0, w + padding().left+padding().right, h + padding().top+padding().bottom});
            child->set_frame(area());
        }
        add_child(child);
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

    void Button::move_fixed(int x, int y) noexcept {
        set_fix_position(true);
        move(x, y);
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
        return frame().size;
    }
    Size Button::size_max() const noexcept {
        return frame().size;
    }

}
