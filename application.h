//
// Created by piotr on 05.02.25.
//

#pragma once

/*------- include files:
-------------------------------------------------------------------*/
#include "types.h"
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
        std::vector<std::shared_ptr<Window>> windows_{};

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
        void add_child(std::shared_ptr<Window> win) noexcept;

    private:
        void main_loop() noexcept;
        void update();
        bool can_exit();
        static void displays();

        friend Window;
    };
}