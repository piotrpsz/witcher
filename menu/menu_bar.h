//
// Created by piotr on 08.02.25.
//

#pragma once

#include "../widget.h"
#include <vector>
#include <string>

namespace Witcher {
    class Button;

    class MenuBar final : public Widget {
        std::vector<Button *> buttons_;
    public:
        explicit MenuBar(Widget* parent);
        ~MenuBar() override;

        void add(std::string const& label) noexcept;

        [[nodiscard]] Size size_min() const noexcept override;
        [[nodiscard]] Size size_max() const noexcept override;
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

