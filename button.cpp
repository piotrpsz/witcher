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

    Button::Button(std::string_view const text, std::function<void()> const& action, Widget* const parent) :
        Widget(ObjectType::Button, parent),
        text_{new Text(text, this)},
        text_selected_(new Text(text, this)),
        action_(action)
    {
        set_parent(parent);
        add_child(text_);
        add_child(text_selected_);
        set_visible(YES);
        set_visible_frame(YES);
        set_resizeable(YES);
    }

    /****************************************************************
    *                                                               *
    *                       p r e p a r e                           *
    *                                                               *
    ****************************************************************/

    void Button::prepare() noexcept {
        text_->set_color(*colors.normal_foreground);
        text_selected_->set_color(*colors.selected_foreground);

        for (const auto child : children()) {
            child->set_parent(this);
            child->prepare();
        }

        // frame().resize(size_max());
        // update_area(frame());
        // text_->prepare();
        // text_selected_->prepare();

        frame().resize(size_min());
        update_area(frame());
        text_->set_frame(area());
        text_selected_->set_frame(area());
    }

    /****************************************************************
    *                                                               *
    *                       p r e p a r e                           *
    *                                                               *
    ****************************************************************/

    void Button::update_geometry() noexcept {
        frame().size.w = size_max().w;
        text_->update_geometry();
        text_selected_->update_geometry();

        // TODO: jeśli rozmiar przycisku większa od size_min() to trzeba wypośrodkować tekst

    }

    /****************************************************************
    *                                                               *
    *                    m o u s e _ d o w n                        *
    *                                                               *
    ****************************************************************/

    void Button::mouse_down(MouseEvent event) noexcept {
        if (focusable()) {
            if (has_focus() && pressed_ && is_three_state()) {
                set_focus(OFF);
                pressed_ = OFF;
                return;
            }
            set_focus(ON);
            pressed_ = ON;
        }
    }

    /****************************************************************
    *                                                               *
    *                    m o u s e _ u p                            *
    *                                                               *
    ****************************************************************/

    void Button::mouse_up(MouseEvent event) noexcept {
        if (has_focus() && !is_three_state())
            tickcounter_ = SDL_GetTicks();
    }

    /****************************************************************
    *                                                               *
    *               m o u s e _ d o u b l e _ d o w n               *
    *                                                               *
    ****************************************************************/

    void Button::mouse_double_down(MouseEvent event) noexcept {
        if (has_focus()) {
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
        if (pressed_) {
            draw::fill_rect(renderer(), frame(), *colors.selected_background);
            if (YES == visible_frame())
                draw::rect(renderer(), frame(), thema::RED_2);
            text_selected_->draw();
        } else {
            draw::fill_rect(renderer(), frame(), *colors.normal_background);
            if (visible_frame())
                draw::rect(renderer(), frame(), thema::RED_1);
            text_->draw();
        }
    }

    Size Button::size_min() const noexcept {
        // When the button contains an image, its size must also be taken into account
        const auto [w, h] = text_->frame().size;
        return {
            .w = w + padding().left + padding().right,
            .h = h + padding().top + padding().bottom};
    }

    Size Button::size_max() const noexcept {
        const auto [w, h] = parent()->frame().size;
        return {
            .w = w - padding().left - padding().right,
            .h = h - padding().top - padding().bottom};
    }

}
