//
// Created by piotr on 05.02.25.
//

#pragma once

#include "widget.h"
#include "mouse_event.h"
#include <string_view>
#include <optional>

namespace Witcher {
    class Text;

    class Button : public Widget {
        Text* text_;
        bool pressed_ = false;
        std::optional<u64> tickcounter_{};
    public:
        explicit Button(std::string_view text, Widget* parent = nullptr);
        ~Button() override = default;

        [[nodiscard]] Size size_min() const noexcept override;
        [[nodiscard]] Size size_max() const noexcept override;
        void mouse_down(MouseEvent event) noexcept override;
        void mouse_up(MouseEvent event) noexcept override;
        void mouse_double_down(MouseEvent event) noexcept override;
        void mouse_double_up(MouseEvent event) noexcept override;

        void move_fixed(int x, int y) noexcept override;
        void update() noexcept override;
        void update_geometry() noexcept override;
        void draw() noexcept override;
        void prepare() noexcept override;

    private:
    };
}
