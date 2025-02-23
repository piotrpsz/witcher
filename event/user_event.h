//
// Created by piotr on 10.02.25.
//

#pragma once

#include "../types.h"
#include <variant>
#include <vector>
#include <string>

namespace Witcher {
    using Variant = std::variant<
        std::monostate,
        int, uint,
        i64, u64,
        f32, f64,
        std::pair<int, int>,
        std::pair<uint, uint>,
        std::pair<f32,f32>,
        std::string,
        Point,
        Size,
        Rect>;

    class UserEvent {
        uint id_{};
        std::vector<Variant> data_{};
    public:
        template <typename... T>
        explicit UserEvent(int const id, T... args) :id_(id) {
            (..., data_.push_back(args));
        }
        // no move
        UserEvent(UserEvent&&) = delete;
        UserEvent& operator=(UserEvent&&) = delete;
        // copy is ok
        UserEvent(UserEvent const&) = default;
        UserEvent& operator=(UserEvent const&) = default;
        // destructor
        ~UserEvent() = default;

        uint id() const noexcept { return id_; }
        std::vector<Variant> data() && { return std::move(data_); }
        [[nodiscard]] std::vector<Variant> const& data() const& { return std::move(data_); }
    public:
        enum {
            MouseMove = 1,
            MouseDown = 2,
            MouseUp = 3,


            QuitRequest = 1000,
        };
    };
}
