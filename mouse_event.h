//
// Created by piotr on 02.02.25.
//

#pragma once

#include "types.h"
#include <format>
#include <SDL3/SDL.h>

namespace Witcher {
    enum class MouseButton {
        Unknown,
        Left,
        Middle,
        Right,
    };

    class MouseEvent {
        SDL_MouseButtonEvent event_{};
        MouseButton button_{};
    public:
        MouseEvent() = default;
        explicit MouseEvent(SDL_MouseButtonEvent const& event) : event_(event) {
            if (event_.button == SDL_BUTTON_LEFT)
                button_ = MouseButton::Left;
            else if (event_.button == SDL_BUTTON_RIGHT)
                button_ = MouseButton::Right;
            else if (event_.button == SDL_BUTTON_MIDDLE)
                button_ = MouseButton::Middle;
            else
                button_ = MouseButton::Unknown;
        }

        [[nodiscard]] std::pair<f32, f32> pos() const noexcept { return {event_.x, event_.y}; }
        [[nodiscard]] uint clicks() const noexcept { return event_.clicks; }
        [[nodiscard]] u64 timestamp () const noexcept { return event_.timestamp / 1'000'000; }
        [[nodiscard]] MouseButton button() const noexcept { return button_; }

        static std::string button(MouseButton const button) noexcept {
            if (button == MouseButton::Left) return "Left";
            if (button == MouseButton::Middle) return "Middle";
            if (button == MouseButton::Right) return "Right";
            return "Unknown";
        }
    };
}

template <>
struct std::formatter<Witcher::MouseEvent> : std::formatter<std::string> {
    auto format(Witcher::MouseEvent const& e, format_context& ctx) const {
        auto const [x, y] = e.pos();
        return formatter<string>::format(std::format("MouseEvent [pos: ({}, {}), button: {}, clicks: {}, timestamp: {}]",
            x, y, Witcher::MouseEvent::button(e.button()), e.clicks(), e.timestamp()), ctx);
    }
};