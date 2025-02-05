//
// Created by piotr on 05.02.25.
//

#pragma once

/*------- include files:
-------------------------------------------------------------------*/
#include "widget.h"
#include <optional>

namespace Witcher {

    class Window : public Widget {
        SDL_Window* window_{};
        SDL_DisplayID display_id_{};
    public:
        explicit Window(std::string const& title, int width, int height);
        ~Window() override;

        void show() noexcept;

    private:
        std::optional<Size> window_size() const noexcept;
        std::optional<Point> window_pos() const noexcept;
        void update_frame() noexcept;

        void move(int x, int y) noexcept;
        void move_center(int display) noexcept;
        void resize(int width, int height) noexcept;

    };

}
