//
// Created by piotr on 09.02.25.
//

#pragma once
#include "../widgets/button/button.h"
#include "../widgets/button/action.h"
#include <optional>

namespace Witcher {
    class Menu;

    class MenuButton final : public Button {
        std::optional<Menu*> menu_{};
    public:
        explicit MenuButton(std::string text, Widget* const parent) : MenuButton(std::move(text), Action(), parent) {}
        MenuButton(std::string text, Action action, Widget* parent);
        ~MenuButton() noexcept override = default;

        MenuButton* add(std::string text, Action action = {}) noexcept;
        MenuButton* add(std::string text, std::function<void()> fn) noexcept {
            return add(std::move(text), std::move(Action(fn)));
        }

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
