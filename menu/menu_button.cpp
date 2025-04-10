//
// Created by piotr on 09.02.25.
//

#include "menu_button.h"
#include "menu_bar.h"
#include "menu.h"
#include "../thema.h"
#include "../event/event_controller.h"
#include "../widgets/dialog/dialog.h"

namespace Witcher {
    MenuButton::MenuButton(std::string text, Action action, Widget* const parent)
        : Button(std::move(text), std::move(action), parent)
    {
        colors.normal_background = thema::DEFAULT_MENU_BACKGROUND;
        colors.normal_foreground = thema::LIGHT_3;
        colors.selected_background = thema::LIGHT_5; //DEFAULT_WINDOW_BACKGROUND;
        colors.selected_foreground = thema::DARK_5;
        set_three_state(YES);
        set_visible_frame(YES);
    }

    /// When we add another menu-button to a menu-button,
    /// it means adding a submenu with that new menu-button.
    MenuButton* MenuButton::add(std::string text, Action action) noexcept {
        if (!menu_)
            menu_ = new Menu(this);

        if (menu_)
            if (auto const btn = menu_.value()->add(std::move(text), std::move(action)))
                return btn;

        return {};
    }

    bool MenuButton::has_submenu() const noexcept {
        return menu_.has_value();
    }

    /// Checking if a point applies to a button.
    /// The specificity of this check is that we check not only the button itself,
    /// but also its submenu.
    Object* MenuButton::contains_point(std::pair<f32,f32> const point) noexcept {
        if (menu_)
            if (auto const obj = menu_.value()->contains_point(point))
                return obj;

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
        if (is_callable()) {
            // Dialog::show("MenuButton", text(), SDL_GL_GetCurrentWindow());
            deactivate();
        }
        Button::mouse_up(event);
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
