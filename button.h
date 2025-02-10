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
        Text* text_selected_;
        bool pressed_ = false;
        bool three_state_ = false;
        std::optional<u64> tickcounter_{};
    public:
        explicit Button(std::string_view text, Widget* parent = nullptr);
        ~Button() override = default;

        void set_three_state(bool const state) noexcept { three_state_ = state; }
        [[nodiscard]] bool is_three_state() const noexcept { return three_state_; }

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
