//
// Created by piotr on 26.02.25.
//

#pragma once

#include <functional>
#include <optional>

namespace Witcher {
    class Action {
        std::optional<std::function<void()>> action_{};
    public:
        explicit Action(std::optional<std::function<void()>> action) : action_(std::move(action)) {}
        Action(const Action&) = delete;
        Action& operator=(const Action&) = delete;
        Action(Action&&) = default;
        Action& operator=(Action&&) = default;
        Action() = default;
        ~Action() = default;

        void call() const noexcept {
            if (action_)
                action_.value()();
        }
        [[nodiscard]] bool is_callable() const noexcept {
            return action_.has_value();
        }
    };
}