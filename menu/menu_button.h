//
// Created by piotr on 09.02.25.
//

#pragma once
#include "../widget/button/button.h"
#include <string_view>
#include <optional>

namespace Witcher {
    class Menu;

    class MenuButton final : public Button {
        std::optional<Menu*> menu_{};
    public:
        explicit MenuButton(std::string text, Widget* const parent) : MenuButton(std::move(text), Action(), parent) {}
        MenuButton(std::string text, Action&& action, Widget* parent);
        ~MenuButton() override = default;

        void add_items(std::string label, std::function<void()>&& action) noexcept;
        void prepare() noexcept override;
        [[nodiscard]] bool has_submenu() const noexcept;
        [[nodiscard]] Menu* get_submenu() const noexcept {
            return menu_.value();
        }

        void deactivate() noexcept override {
            parent()->deactivate();
        }
        Object* contains_point(std::pair<f32,f32> point) noexcept override;
        void mouse_down(MouseEvent) noexcept override;
        void mouse_up(MouseEvent) noexcept override;
        void update_geometry() noexcept override;
        void draw() noexcept override;

        friend class MenuBar;
    };
}
