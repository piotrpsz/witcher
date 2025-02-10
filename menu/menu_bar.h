//
// Created by piotr on 08.02.25.
//

#pragma once

#include "../widget.h"
#include <vector>
#include <string>

namespace Witcher {
    class MenuButton;

    class MenuBar final : public Widget {
        std::vector<MenuButton*> buttons_;
    public:
        explicit MenuBar(Widget* parent);
        ~MenuBar() override;

        void add(std::string const& label) noexcept;

        [[nodiscard]] Size size_min() const noexcept override;
        [[nodiscard]] Size size_max() const noexcept override;

        Object* contains_point(f32 x, f32 y) noexcept override;
        void user_event(UserEvent) noexcept override;

        void mouse_down(MouseEvent event) noexcept override;
        void mouse_up(MouseEvent event) noexcept override;
        void mouse_double_down(MouseEvent event) noexcept override;
        void mouse_double_up(MouseEvent event) noexcept override;

        void update() noexcept override;
        void update_geometry() noexcept override;
        void draw() noexcept override;
        void prepare() noexcept override;
    };
}

