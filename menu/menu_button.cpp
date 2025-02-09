//
// Created by piotr on 09.02.25.
//

#include "menu_button.h"
#include "../thema.h"

namespace Witcher {
    MenuButton::MenuButton(std::string_view const text, Widget* const parent) : Button(text, parent) {
        colors.normal_background = thema::DEFAULT_MENU_BACKGROUND;
        colors.normal_foreground = thema::LIGHT_3;
        colors.selected_background = thema::DARK_3;
    }

}