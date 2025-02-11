//
// Created by piotr on 09.02.25.
//

#include "menu_button.h"
#include "menu_bar.h"
#include "../thema.h"
#include "../toolbox/toolbox.h"
#include "../toolbox/crypto/crypto.h"

namespace Witcher {
    MenuButton::MenuButton(std::string_view const text, MenuBar* const parent) : Button(text, parent) {
        colors.normal_background = thema::DEFAULT_MENU_BACKGROUND;
        colors.normal_foreground = thema::LIGHT_3;
        colors.selected_background = {0, 50, 60, 255};
        colors.selected_foreground = thema::LIGHT_2;
        set_three_state(ON);
        bee::box::println("MenuButton::MenuButton. This: {}, Parent: {}", static_cast<void *>(this), static_cast<void *>(parent));
    }

    void MenuButton::mouse_down(MouseEvent const event) noexcept {
        Button::mouse_down(event);
        if (has_focus())
            if (auto const bar = dynamic_cast<MenuBar*>(parent()))
                bar->set_active_menu_button(this);
    }

}
