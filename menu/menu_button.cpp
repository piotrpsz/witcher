//
// Created by piotr on 09.02.25.
//

#include "menu_button.h"
#include "menu_bar.h"
#include "menu.h"
#include "../thema.h"
#include "../toolbox/toolbox.h"
#include "../toolbox/crypto/crypto.h"

namespace Witcher {
    MenuButton::MenuButton(std::string_view const text, std::function<void()>&& action, Widget* const parent)
        : Button(text, std::move(action), parent)
    {
        colors.normal_background = thema::DEFAULT_MENU_BACKGROUND;
        colors.normal_foreground = thema::LIGHT_3;
        colors.selected_background = thema::LIGHT_5; //DEFAULT_WINDOW_BACKGROUND;
        colors.selected_foreground = thema::DARK_5;
        set_three_state(YES);
        set_visible_frame(YES);

        // bee::box::println_ptr()
    }

    void MenuButton::add_items(std::string_view const label, std::function<void()>&& action) noexcept {
        if (!menu_)
            menu_ = new Menu(this);
        if (menu_)
            menu_.value()->add(label, std::move(action));
    }

    bool MenuButton::has_submenu() const noexcept {
        return menu_.has_value() && menu_.value()->visible();
    }

    /// Checking if a point applies to a button.
    /// The specificity of this check is that we check not only the button itself,
    /// but also its submenu.
    Object* MenuButton::contains_point(std::pair<f32,f32> const point) noexcept {
        if (menu_) {
            // bee::box::println("menu frame: {}, point: {}", menu_.value()->frame(), point);

            if (auto const obj = menu_.value()->contains_point(point)) {
                // bee::box::println_ptr(obj, "MenuButton::contains_point, found button menu frame: {}, point: {}", menu_.value()->frame(), point);
                return obj;
            }
        }
        // bee::box::println_ptr(this, "button {}, frame: {}, point: {} ({})", text(), frame(), point, frame().contains_point(point));
        return frame().contains_point(point) ? this : nullptr;
    }

    void MenuButton::mouse_down(MouseEvent const event) noexcept {
        // bee::box::println("MenuButton::mouse_down IN");
        Button::mouse_down(event);
        if (auto const bar = dynamic_cast<MenuBar*>(parent()))
            bar->set_active_menu_button(has_focus() ? this : nullptr);

        if (menu_)
            menu_.value()->set_visible(!menu_.value()->visible());
    }

    void MenuButton::mouse_up(MouseEvent const event) noexcept {
        // bee::box::println("MouseButton::mouse_up: IN");
            action();
    }

    void MenuButton::prepare() noexcept {
        Button::prepare();
        if (menu_)
            menu_.value()->prepare();
    }

    void MenuButton::update_geometry() noexcept {
        if (menu_)
            menu_.value()->update_geometry();
    }

    void MenuButton::draw() noexcept {
        Button::draw();
        if (menu_)
            menu_.value()->draw();
    }

}
