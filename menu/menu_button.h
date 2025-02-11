//
// Created by piotr on 09.02.25.
//

#pragma once
#include "../button.h"
#include <string_view>

namespace Witcher {
    class MenuBar;

    class MenuButton final : public Button {
    public:
        explicit MenuButton(std::string_view text, MenuBar* parent);
        ~MenuButton() override = default;

        void mouse_down(MouseEvent) noexcept override;
    };
}
