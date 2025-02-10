//
// Created by piotr on 09.02.25.
//

#include "menu_button.h"
#include "../thema.h"

namespace Witcher {
    MenuButton::MenuButton(std::string_view const text, Widget* const parent) : Button(text, parent) {
        colors.normal_background = thema::DEFAULT_MENU_BACKGROUND;
        colors.normal_foreground = thema::LIGHT_3;
        colors.selected_background = {0, 50, 60, 255};
        colors.selected_foreground = thema::LIGHT_2;
        set_three_state(ON);
    }

}