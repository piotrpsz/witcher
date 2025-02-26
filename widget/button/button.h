//
// Created by piotr on 05.02.25.
//

#pragma once

#include "../../widget.h"
#include "../../mouse_event.h"
#include <string_view>
#include <optional>
#include <functional>
#include "../../text.h"
#include "action.h"

namespace Witcher {
    class Button : public Widget {
        Text* text_;
        Text* text_selected_;
        bool pressed_ = false;
        bool three_state_ = false;
        std::optional<u64> tickcounter_{};
        Action action_;
    public:
        Button(std::string text, Action&& action, Widget* parent = nullptr);

        Button(std::string text, std::function<void()>&& action, Widget* const parent = nullptr) :
            Button(std::move(text), Action(action), parent) {}

        explicit Button(std::string text, Widget* parent = nullptr) :
            Button(std::move(text), Action(), parent) {}

        ~Button() override = default;

        [[nodiscard]] std::string text() const noexcept {
            return text_->text();
        }
        void set_pressed(bool const pressed = true) noexcept { pressed_ = pressed; }
        [[nodiscard]] bool pressed() const noexcept {return pressed_;}
        // void action() const noexcept { action_.run(); }

        bool is_callable() const noexcept { return action_.is_callable(); }

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
