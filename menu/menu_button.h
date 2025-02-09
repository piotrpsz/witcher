//
// Created by piotr on 09.02.25.
//

#pragma once
#include "../button.h"
#include <string_view>

namespace Witcher {
    class MenuButton final : public Button {
    public:
        explicit MenuButton(std::string_view text, Widget* parent);
        ~MenuButton() override = default;
    };
}
