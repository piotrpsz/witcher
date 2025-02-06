//
// Created by piotr on 05.02.25.
//

/*------- include files:
-------------------------------------------------------------------*/
#include "window.h"

#include "thema.h"
#include "types.h"
#include "toolbox/all.h"

namespace Witcher {
    using namespace bee;

    Window::Window(std::string const& title, int width, int height) :
        Widget(ObjectType::Window, this)
    {
        constexpr auto flags =
            SDL_WINDOW_RESIZABLE
            | SDL_WINDOW_HIDDEN
            | SDL_WINDOW_HIGH_PIXEL_DENSITY
            | SDL_WINDOW_INPUT_FOCUS
            | SDL_WINDOW_MOUSE_FOCUS;
        SDL_Renderer* renderer;
        if (!SDL_CreateWindowAndRenderer(title.c_str(), 0, 0, flags, &window_, &renderer)) {
            box::print_error("Failed to create window and renderer: {}\n", SDL_GetError());
            exit(1);
        }
        set_renderer(renderer);

        display_id_ = SDL_GetDisplayForWindow(window_);
        SDL_HideWindow(window_);
        set_focusable(true);
    }

    Window::~Window() {
        SDL_DestroyRenderer(renderer());
        SDL_DestroyWindow(window_);
    }

    /****************************************************************
    *                                                               *
    *                       p r e p a r e                           *
    *                                                               *
    ****************************************************************/

    void Window::prepare() noexcept {
        update_frame();
        update_geometry();
        for (const auto it : children()) {
            it->set_parent(this);
            it->prepare();
        }
    }


    void Window::show() noexcept {
        SDL_ShowWindow(window_);
        set_visible(true);
    }

    void Window::move(int const x, int const y) noexcept {
        if (SDL_SetWindowPosition(window_, x, y)) {
            update_frame();
            return;
        }
        box::print_error("Failed to move window to position: {}\n", SDL_GetError());
    }

    void Window::update_geometry() noexcept {
        for (auto const child : children()) {
            child->update_geometry();
        }
    }

    void Window::move_center(int display) noexcept {
        int display_count{};
        SDL_DisplayID* const ptr = SDL_GetDisplays(&display_count);
        if (display_count >= display)
            display = display_count - 1;

        SDL_Rect display_rect{};
        if (SDL_GetDisplayUsableBounds(display, &display_rect)) {
            if (auto size = window_size()) {
                auto const [w, h] = size.value();
                auto const x = display_rect.x + (display_rect.w - w) / 2;
                auto const y = display_rect.y + (display_rect.h - h) / 2;
                move(x, y);
                return;
            }
        }
        box::print_error("Failed to move window to center: {}\n", SDL_GetError());
    }

    void Window::resize(int const width, int const height) noexcept {
        if (SDL_SetWindowSize(window_, width, height)) {
            update_frame();
            return;
        }
        box::print_error("Failed to resize window: {}\n", SDL_GetError());
    }

    std::optional<Size> Window::window_size() const noexcept {
        Size size{};
        if (SDL_GetWindowSize(window_, &size.w, &size.h))
            return size;

        box::print_error("Failed to get size of window: {}\n", SDL_GetError());
        return {};
    }

    Object* Window::contains_point(f32 const x, f32 const y) noexcept {
        if (focusable()) {
            for (auto const child : children())
                if (child->contains_point(x, y))
                    return child;

            return this;
        }
        return {};
    }

    std::optional<Point> Window::window_pos() const noexcept {
        Point pos{};
        if (SDL_GetWindowPosition(window_, &pos.x, &pos.y))
            return pos;

        box::print_error("Failed to get pos of window: {}\n", SDL_GetError());
        return {};
    }


    void Window::update_frame() noexcept {
        if (SDL_SyncWindow(window_)) {
            if (auto const pos = window_pos()) {
                if (auto const size = window_size()) {
                    frame().pos = *pos;
                    frame().size = *size;
                    return;
                }
            }
        }
        box::print_error("Failed to update window's frame: {}\n", SDL_GetError());
    }


    void Window::update() noexcept {
        for (const auto child: children()) {
            child->update();
        }
    }

    void Window::draw() noexcept {
        auto const [r, g, b, a] = thema::DEFAULT_WINDOW_BACKGROUND;
        SDL_SetRenderDrawColor(renderer(), r, g, b, a);
        SDL_RenderClear(renderer());

        for (const auto child: children())
            child->draw();

        SDL_RenderPresent(renderer());
    }
}
