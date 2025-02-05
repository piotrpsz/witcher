//
// Created by piotr on 05.02.25.
//

#pragma once

#include "widget.h"
#include "mouse_event.h"
#include <optional>

namespace Witcher {
    class Text;

    class Button : public Widget {
        bool pressed_ = false;
        std::optional<u64> tickcounter_{};
    public:
        explicit Button(std::string text, Widget* parent = nullptr);
        ~Button() override = default;

        Size size_min() const noexcept override;
        Size size_max() const noexcept override;
        void mouse_down(MouseEvent &&event) noexcept override;
        void mouse_up(MouseEvent &&event) noexcept override;
        void mouse_double_down(MouseEvent &&event) noexcept override;
        void mouse_double_up(MouseEvent &&event) noexcept override;

        void update() noexcept override;
        void draw() noexcept override;

    private:
    };
}
