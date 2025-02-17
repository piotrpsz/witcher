//
// Created by piotr on 08.02.25.
//

#include "menu_bar.h"
#include "menu_button.h"
#include "../event/event_controller.h"
#include "../types.h"
#include "../toolbox/all.h"
#include "../helpers/draw.h"
#include "../thema.h"
#include <numeric>
#include <algorithm>

namespace Witcher {
    using namespace bee;

    MenuBar::MenuBar(Widget *parent) : Widget(ObjectType::MenuBar, parent) {
        set_parent(parent);
        set_visible(true);
        // set_visible_frame(YES);
        set_resizeable(true);
        EventController::self().append(this, UserEvent::MouseMove);
        EventController::self().print_content();
    }

    MenuBar::~MenuBar() {
        EventController::self().remove(this);
        EventController::self().print_content();
    }

    void MenuBar::user_event(UserEvent const event) noexcept {
        switch (event.id()) {
            case UserEvent::MouseMove:
                if (active_frame_) {
                    if (auto const& data = event.data(); !data.empty()) {
                        if (auto const point = std::get<std::pair<f32, f32>>(data[0]); active_frame_->contains_point(point)) {
                            refocus(point);
                            return;
                        }
                    }
                }
                deactivate();
                break;;
            default: {}
        }
    }

    MenuButton* MenuBar::add(std::string const& label) noexcept {
        auto const button = new MenuButton(label, this);
        button->set_visible_frame(false);
        button->padding() = {.left = 0, .top = 3, .right = 0, .bottom = 3};
        buttons_.push_back(button);
        return button;
    }

    Size MenuBar::size_min() const noexcept {
        Size min{};
        for (auto const& button : buttons_) {
            if (button->visible()) {
                auto const [w, h] = button->size_min();
                min.w += w;
                min.h = std::max(min.h, h);
            }
            // 3 pixels gap between buttons
            min.w += static_cast<int>(buttons_.size() - 1);
            return {min.w, min.h};
        }
        return min;
    }

    void MenuBar::prepare() noexcept {
        // box::println("MenuBar::prepare IN");

        for (auto const& button : buttons_)
            button->prepare();

        auto frame = parent()->frame();
        auto [w, h] = size_min();
        frame.pos = {};
        frame.size.h = h;
        set_frame(frame);
        update_geometry();
    };

    void MenuBar::update_geometry() noexcept {
        // box::println("MenuBar::update_geometry IN");

        auto x = 1;
        for (auto const& button : buttons_) {
            button->move(x, 0);
            button->update_geometry();
            x += button->size_min().w;
            x += 2;
        }
    };

    Size MenuBar::size_max() const noexcept {
        return frame().size;
    }


    Object *MenuBar::contains_point(f32 const x, f32 const y) noexcept {
        if (frame().contains_point(x, y)) {
            for (auto const& button : buttons_)
                if (button->contains_point(x, y))
                    return button;
            return this;
        }
        return nullptr;
    }

    void MenuBar::mouse_down(MouseEvent event) noexcept {

    }

    void MenuBar::mouse_up(MouseEvent event) noexcept {}
    void MenuBar::mouse_double_down(MouseEvent event) noexcept {}
    void MenuBar::mouse_double_up(MouseEvent event) noexcept {}

    void MenuBar::update() noexcept {};

    /****************************************************************
    *                                                               *
    *                           d r a w                             *
    *                                                               *
    ****************************************************************/

    void MenuBar::draw() noexcept {
        // Fill background
        draw::fill_rect(renderer(), frame(), thema::DEFAULT_MENU_BACKGROUND);
        // Draw frame if needed
        if (visible_frame())
            draw::rect(renderer(), frame(), thema::RED_5);
        // Draw buttons
        for (auto const& button : buttons_)
            button->draw();
    };

    /****************************************************************
    *                                                               *
    *                       P R I V A T E                           *
    *                                                               *
    ****************************************************************/

    void MenuBar::set_active_menu_button(MenuButton* button) noexcept {
        auto const y = buttons_.front()->frame().pos.y;
        auto const h = buttons_.front()->frame().size.h;
        auto const xl = buttons_.front()->frame().pos.x;
        auto const xr = buttons_.back()->frame().pos.x + buttons_.back()->frame().size.w - 1;
        active_frame_ = Rect{
            .pos = {xl, y},
            .size = {xr - xl, h} };

        active_menu_button_ = button;
    }

    /****************************************************************
    *                                                               *
    *                     d e a c t i v a t e                       *
    *                                                               *
    ****************************************************************/

    void MenuBar::deactivate() noexcept {
        active_frame_ = {};
        if (active_menu_button_) {
            active_menu_button_->mouse_down({});
            active_menu_button_ = nullptr;
        }
    }


    /****************************************************************
    *                                                               *
    *                       r e f o c u s                           *
    *                                                               *
    ****************************************************************/

    void MenuBar::refocus(std::pair<f32, f32> pos) noexcept {
        auto&& [x, y] = pos;
        // box::println("MenuBar::refocus IN ({})", pos);

        // When we have an active button...
        if (active_menu_button_) {
            // ... and when this particular button contains coordinates, we do nothing
            if (active_menu_button_->contains_point(x, y))
                return;

            // otherwise it ceases to be an active button.
            active_menu_button_->mouse_down({});
            active_menu_button_ = nullptr;
        }

        // Otherwise, the active button will be the button containing these coordinates
        for (auto const& button : buttons_) {
            if (button->contains_point(x, y)) {
                button->mouse_down({});
                active_menu_button_ = button;
                return;
            }
        }
    }

}