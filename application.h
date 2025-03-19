//
// Created by piotr on 05.02.25.
//

#pragma once

/*------- include files:
-------------------------------------------------------------------*/
#include "types.h"
#include "window.h"
#include <string>
#include <vector>
#include <memory>

namespace Witcher {
    class Window;

    class Application final {
        static constexpr u64 DEADLINE = 10; // milliseconds

        std::string const name_;
        std::string const version_;
        std::string const identifier_;
        std::string const creator_;
        std::string const copyright_;
        Window* window_{};

        u64 tick_counter_{};

    public:
        Application(
            std::string app_name,
            std::string app_version,
            std::string app_identifier,
            std::string app_creator = "",
            std::string app_copyright = "");
        ~Application();
        void run() noexcept;

    private:
        void main_loop() noexcept;
        void update();
        [[nodiscard]] bool can_exit() const noexcept;
        static void displays();
        static std::string pixel_format(SDL_PixelFormat) noexcept;

        friend Window;
    };
}