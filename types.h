//
// Created by piotr on 30.01.25.
//
#pragma once

/*------- include files:
---------------------------------------------------------*/
#include <cstdint>
#include <format>
#include <SDL3/SDL_pixels.h>
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

    constexpr bool ON = true;
    constexpr bool OFF = false;
    constexpr bool YES = true;
    constexpr bool NO = false;

    enum class ObjectType {
        None = 0,
        MenuBar,
        Text, Button, Layout,
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
        void resize(Size const new_size) noexcept {
            size = new_size;
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
        [[nodiscard]] bool contains_point(std::pair<f32,f32> const pos) const noexcept {
            return contains_point(pos.first, pos.second);
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
    struct Colors {
        std::optional<SDL_Color> normal_background{};
        std::optional<SDL_Color> normal_foreground{};
        std::optional<SDL_Color> selected_background{};
        std::optional<SDL_Color> selected_foreground{};
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

template <>
struct std::formatter<SDL_Rect> : std::formatter<std::string> {
    auto format(SDL_Rect const& r, format_context& ctx) const {
        return formatter<std::string>::format(std::format("[({},{}), ({},{})]", r.x, r.y, r.w,  r.h), ctx);
    }
};

template <>
struct std::formatter<std::pair<Witcher::f32,Witcher::f32>> : std::formatter<std::string> {
    auto format(std::pair<Witcher::f32,Witcher::f32> const& pair, format_context& ctx) const {
        return formatter<std::string>::format(std::format("({},{})", pair.first, pair.second), ctx);
    }
};