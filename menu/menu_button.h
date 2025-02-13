//
// Created by piotr on 09.02.25.
//

#pragma once
#include "../button.h"
#include <string_view>
#include <optional>

namespace Witcher {
    class Menu;

    class MenuButton final : public Button {
        std::optional<Menu*> menu_{};
    public:
        explicit MenuButton(std::string_view text, Widget* parent);
        ~MenuButton() override = default;

        void add_items(std::string_view label, std::function<void()> const& action) noexcept;
        void prepare() noexcept override;

        void mouse_down(MouseEvent) noexcept override;
        void draw() noexcept override;
    };
}
