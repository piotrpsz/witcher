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
        explicit MenuButton(std::string_view text, std::function<void()> const& action, Widget* parent);
        ~MenuButton() override = default;

        void add_items(std::string_view label, std::function<void()> const& action) noexcept;
        void prepare() noexcept override;
        [[nodiscard]] bool has_submenu() const noexcept;
        [[nodiscard]] Menu* get_submenu() const noexcept {
            return menu_.value();
        }

        void mouse_down(MouseEvent) noexcept override;
        void update_geometry() noexcept override;
        void draw() noexcept override;

        friend class MenuBar;
    };
}
