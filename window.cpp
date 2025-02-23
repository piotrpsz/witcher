//
// Created by piotr on 05.02.25.
//

/*------- include files:
-------------------------------------------------------------------*/
#include "window.h"
#include "application.h"
#include "thema.h"
#include "types.h"
#include "toolbox/all.h"

namespace Witcher {
    using namespace bee;

    Window::Window(Application& app, std::string const& title, int width, int height) :
        Widget(ObjectType::Window, this)
    {
        constexpr auto flags =
            SDL_WINDOW_RESIZABLE
            | SDL_WINDOW_HIDDEN
            | SDL_WINDOW_HIGH_PIXEL_DENSITY
            | SDL_WINDOW_INPUT_FOCUS
            | SDL_WINDOW_MOUSE_FOCUS;
        SDL_Renderer* renderer;
        if (!SDL_CreateWindowAndRenderer(title.c_str(), width, height, flags, &window_, &renderer)) {
            box::print_error("Failed to create window and renderer: {}\n", SDL_GetError());
            exit(1);
        }
        set_renderer(renderer);

        display_id_ = SDL_GetDisplayForWindow(window_);
        SDL_HideWindow(window_);
        set_focusable(true);

        // Register the window in application.
        app.window_ = this;

        box::println("Window::Window");
    }

    Window::~Window() {
        if (menu_bar_)
            delete menu_bar_;
        SDL_DestroyRenderer(renderer());
        SDL_DestroyWindow(window_);
    }

    bool Window::user_quit_request() noexcept {
        if (can_close()) {
            auto close_window_request = SDL_Event{.type = SDL_EVENT_WINDOW_CLOSE_REQUESTED};
            SDL_PushEvent(&close_window_request);
            auto quit_request = SDL_Event{.type = SDL_EVENT_QUIT};
            SDL_PushEvent(&quit_request);
            return true;
        }
        return false;
        /*
        SDL_Event event;
        SDL_zero(event);
        event.type = SDL_EVENT_QUIT;
        // event.user.code = UserEvent::QuitRequest;
        // event.user.data1 = nullptr;
        // event.user.data2 = nullptr;

        // event.type = SDL_EVENT_USER;
        // event.user.code = UserEvent::QuitRequest;
        // event.user.data1 = nullptr;
        // event.user.data2 = nullptr;
        SDL_PushEvent(&event);
        */
    }

    bool Window::set_content(Object* const content) noexcept {
        if (children().empty()) {
            add_child(content);
            return true;
        }
        box::println_error("Failed to set content. The window already has content.");
        return {};
    }


    /****************************************************************
    *                                                               *
    *                       p r e p a r e                           *
    *                                                               *
    ****************************************************************/

    void Window::prepare() noexcept {
        update_frame();

        if (menu_bar_)
            menu_bar_->prepare();

        for (const auto it : children()) {
            it->set_parent(this);
            it->prepare();
        }
    }


    void Window::show() noexcept {
        SDL_ShowWindow(window_);
        set_visible(true);
        move(frame().pos.x, frame().pos.y);
        update_geometry();
    }

    void Window::move(int const x, int const y) noexcept {
        if (SDL_SetWindowPosition(window_, x, y)) {
            update_frame();
            return;
        }
        box::print_error("Failed to move window to position: {}\n", SDL_GetError());
    }

    void Window::update_geometry() noexcept {
        update_frame();
        // box::println("Window::update_geometry {}", frame().size);

        if (menu_bar_)
            menu_bar_->update_geometry();

        for (auto const child : children())
            child->update_geometry();
    }

    void Window::move_center(int display) noexcept {
        int display_count{};
        SDL_DisplayID const* const screen = SDL_GetDisplays(&display_count);
        if (display > (display_count - 1))
            display = display_count - 1;

        SDL_Rect display_rect{};
        if (SDL_GetDisplayBounds(screen[display], &display_rect)) {
            if (auto size = window_size()) {
                auto const [w, h] = size.value();
                auto const name = std::string(SDL_GetDisplayName(screen[display])).c_str();
                // box::println("Selected display: {}, {}\n", name, display_rect);
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
            // update_frame();
            update_geometry();
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
            if (menu_bar_) {
                if (auto const obj = menu_bar_->contains_point(x, y)) {
                    box::println_ptr(obj, "Window::contains_point in menu bar");
                    return obj;
                }
            }

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
                    // box::println("Window::update_frame, window frame: {}", frame());
                    return;
                }
            }
        }
        box::print_error("Failed to update window's frame: {}\n", SDL_GetError());
        exit(1);
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

        if (menu_bar_) menu_bar_->draw();

        for (const auto child: children())
            child->draw();

        SDL_RenderPresent(renderer());
    }
}
