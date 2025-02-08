//
// Created by piotr on 05.02.25.
//

#pragma once

/*------- include files:
-------------------------------------------------------------------*/
#include "widget.h"
#include <optional>

#include "layout.h"
#include "menu/menu_bar.h"

namespace Witcher {
    class Application;
    class MenuBar;

    class Window : public Widget {
        MenuBar* menu_bar_{};
        SDL_Window* window_{};
        SDL_DisplayID display_id_{};
    public:
        Window(Application& app, std::string const& title, int width = 640, int height = 400);
        ~Window() override;

        MenuBar* menu_bar() noexcept {
            menu_bar_ = new MenuBar(this);
            return menu_bar_;
        }

        bool set_content(Object* content) noexcept;
        void show() noexcept;

        [[nodiscard]] std::optional<Size> window_size() const noexcept;
        [[nodiscard]] std::optional<Point> window_pos() const noexcept;
        void update_frame() noexcept;

        void move(int x, int y) noexcept override;
        void move_center(int display) noexcept;
        void resize(int width, int height) noexcept;
        [[nodiscard]] Size size_min() const noexcept override { return {}; }
        [[nodiscard]] Size size_max() const noexcept override { return {}; }
        void update() noexcept override;
        void draw() noexcept override;
        // void mouse_down(MouseEvent event) noexcept override;
        // void mouse_up(MouseEvent event) noexcept override;
        // void mouse_double_down(MouseEvent event) noexcept override;
        // void mouse_double_up(MouseEvent event) noexcept override;
        Object* contains_point(f32 x, f32 y) noexcept override;
        void update_geometry() noexcept override;
        void prepare() noexcept override;
    };

}
