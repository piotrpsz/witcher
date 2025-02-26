//
// Created by piotr on 11.02.25.
//

#include "menu.h"
#include "menu_button.h"
#include "../helpers/draw.h"

namespace Witcher {


    Menu::Menu(Widget *parent) : Widget(ObjectType::Menu, parent) {
        set_parent(parent);
        set_resizeable(NO);
        set_visible_frame(YES);
        set_visible(NO);
    }

    void Menu::add(std::string name, std::function<void()>&& action) {
        auto const button = new MenuButton(std::move(name), Action(action), this);
        button->set_visible_frame(NO);
        button->padding() = {.left = 3, .top = 3, .right = 3, .bottom = 3};
        buttons_.push_back(button);
    }

    void Menu::refocus(std::pair<f32, f32> const& point) noexcept {
        MenuButton* new_active_button = nullptr;

        for (auto const button : buttons_) {
            if (button->contains_point(point)) {
                new_active_button = button;
                break;
            }
        }

        if (new_active_button) {
            if (active_menu_button_)
                active_menu_button_->set_pressed(false);
            active_menu_button_ = new_active_button;
            active_menu_button_->set_pressed();
        }

    }


    Object* Menu::contains_point(std::pair<f32, f32> const point) noexcept {
        for (auto const button : buttons_) {
            if (button->contains_point(point))
                return button;
        }
        return nullptr;
    }

    /****************************************************************
    *                                                               *
    *       p u r e l y   v i r t u a l   f r o m   o b j e c t     *
    *                                                               *
    ****************************************************************/

    Size Menu::size_min() const noexcept {
        return frame().size;
    }

    Size Menu::size_max() const noexcept {
        return frame().size;
    }

    void Menu::update() noexcept {
        update_geometry();
    }

    void Menu::prepare() noexcept {
        auto width = 0, height = 0;;
        for (auto const& button : buttons_) {
            button->prepare();
            width = std::max(width, button->frame().size.w);
            height += button->frame().size.h;
        }
        Rect const frame{0, 0, width, height};
        set_frame(frame);
        // update_geometry();
    }

    void Menu::update_geometry() noexcept {
        auto const x = parent()->frame().pos.x;
        auto y = parent()->frame().pos.y + parent()->frame().size.h;
        set_pos(x, y);
        for (auto const& button : buttons_) {
            button->set_pos(x, y);
            button->frame().size.w = frame().size.w;
            y += button->frame().size.h;
        }
    }

    void Menu::draw() noexcept {
        if (visible()) {
            draw::fill_rect(renderer(), frame(), thema::DEFAULT_MENU_BACKGROUND);
            for (auto const& button : buttons_)
                button->draw();
        }
    }

}