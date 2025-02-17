//
// Created by piotr on 08.02.25.
//

#pragma once

#include "../widget.h"
#include <vector>
#include <string>
#include <optional>

namespace Witcher {
    class MenuButton;

    class MenuBar final : public Widget {
        std::vector<MenuButton*> buttons_;
        MenuButton* active_menu_button_{};
        std::optional<Rect> active_buttons_area_{};

    public:
        explicit MenuBar(Widget* parent);
        ~MenuBar() override;

        MenuButton* add(std::string const& label) noexcept;

        [[nodiscard]] Size size_min() const noexcept override;
        [[nodiscard]] Size size_max() const noexcept override;

        Object* contains_point(f32 x, f32 y) noexcept override;
        void user_event(UserEvent) noexcept override;

        void mouse_down(MouseEvent) noexcept override;
        void mouse_up(MouseEvent) noexcept override;
        void mouse_double_down(MouseEvent) noexcept override;
        void mouse_double_up(MouseEvent) noexcept override;

        void update() noexcept override;
        void update_geometry() noexcept override;
        void draw() noexcept override;
        void prepare() noexcept override;

    private:
        void deactivate() noexcept;
        void set_active_menu_button(MenuButton* button) noexcept;
        void refocus(std::pair<f32,f32> pos) noexcept;

        friend class MenuButton;
    };
}

