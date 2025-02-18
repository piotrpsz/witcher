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
    MenuButton::MenuButton(std::string_view const text, std::function<void()> const& action, Widget* const parent)
        : Button(text, action, parent)
    {
        colors.normal_background = thema::DEFAULT_MENU_BACKGROUND;
        colors.normal_foreground = thema::LIGHT_3;
        colors.selected_background = thema::LIGHT_5; //DEFAULT_WINDOW_BACKGROUND;
        colors.selected_foreground = thema::DARK_5;
        set_three_state(YES);
        set_visible_frame(YES);
    }

    void MenuButton::add_items(std::string_view const label, std::function<void()> const& action) noexcept {
        if (!menu_)
            menu_ = new Menu(this);
        if (menu_)
            menu_.value()->add(label, action);
    }

    bool MenuButton::has_submenu() const noexcept {
        return menu_.has_value() && menu_.value()->visible();
    }

    void MenuButton::mouse_down(MouseEvent const event) noexcept {
        Button::mouse_down(event);
        auto const bar = dynamic_cast<MenuBar*>(parent());
        bar->set_active_menu_button(has_focus() ? this : nullptr);

        if (menu_)
            menu_.value()->set_visible(!menu_.value()->visible());
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
