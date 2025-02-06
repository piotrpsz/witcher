//
// Created by piotr on 30.01.25.
//
#pragma once

/*------- include files:
---------------------------------------------------------*/
#include <cstdint>
#include <format>
#include <SDL3/SDL_rect.h>

namespace Witcher {
    using i64 = int64_t;
    using i32 = int32_t;
    using i16 = int16_t;
    using i8 = int8_t;
    using u64 = uint64_t;
    using u32 = uint32_t;
    using u16 = uint16_t;
    using u8 = uint8_t;
    using f32 = float;
    using f64 = double;

    enum class ObjectType {
        None = 0,
        Text, Button,
        HBoxLayout, VBoxLayout, GridLayout,
        Window
    };

    /// Point struct
    struct Point {
        int x{}, y{};
    };
    struct PointF {
        f32 px{}, py{};
    };

    /// Size struct
    struct  Size {
        int w{}, h{};
    };

    /// Rect struct
    struct Rect {
        Point pos;
        Size size;

        void move(int const dx, int const dy) noexcept {
            pos.x += dx;
            pos.y += dy;
        }
        void resize(int const dw, int const dh) noexcept {
            size.w += dw;
            size.h += dh;
        }
        void reduction(int const n) noexcept {
            pos.x += n;
            pos.y += n;
            size.w -= (2 * n);
            size.h -= (2 * n);
        }
        [[nodiscard]] bool contains_point(f32 const x,  f32 const y) const noexcept {
            auto const fx0 = static_cast<f32>(pos.x);
            auto const fy0 = static_cast<f32>(pos.y);
            if (x < fx0 || y < fy0) return {};
            auto const fx1 = fx0 + static_cast<f32>(size.w);
            auto const fy1 = fy0 + static_cast<f32>(size.h);
            if (x > fx1 || y > fy1) return {};
            return true;
        }
        [[nodiscard]] SDL_FRect to_frect() const noexcept {
            return SDL_FRect{
                .x = static_cast<f32>(pos.x),
                .y = static_cast<f32>(pos.y),
                .w = static_cast<f32>(size.w),
                .h = static_cast<f32>(size.h)
            };
        }
    };

    struct Padding {
        int left{}, top{}, right{}, bottom{};
    };
}

template <>
struct std::formatter<Witcher::Point> : std::formatter<std::string> {
    auto format(Witcher::Point const& p, format_context& ctx) const {
        return formatter<std::string>::format(std::format("({}, {})", p.x, p.y), ctx);
    }
};

template <>
struct std::formatter<Witcher::Size> : std::formatter<std::string> {
    auto format(Witcher::Size const& s, format_context& ctx) const {
        return formatter<std::string>::format(std::format("({}, {})", s.w, s.h), ctx);
    }
};

template <>
struct std::formatter<Witcher::Rect> : std::formatter<std::string> {
    auto format(Witcher::Rect const& r, format_context& ctx) const {
        return formatter<std::string>::format(std::format("[{}, {}]", r.pos, r.size), ctx);
    }
};
