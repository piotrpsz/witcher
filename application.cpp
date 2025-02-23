//
// Created by piotr on 05.02.25.
//

/*------- include files:
-------------------------------------------------------------------*/
#include "application.h"
#include "window.h"
#include "types.h"
#include "toolbox/all.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "event/event_controller.h"

namespace Witcher {
    using namespace bee;

    Application::Application(
        std::string app_name,
        std::string app_version,
        std::string app_identifier,
        std::string app_creator,
        std::string app_copyright
    ) :
        name_{std::move(app_name)},
        version_{std::move(app_version)},
        identifier_{std::move(app_identifier)},
        creator_{std::move(app_creator)},
        copyright_{std::move(app_copyright)}
    {
        if (!SDL_SetAppMetadata(name_.c_str(), version_.c_str(), identifier_.c_str()))
            box::println_error("Failed to set application metadata: {}", SDL_GetError());

        if (!creator_.empty())
            if (!SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING, creator_.c_str()))
                box::println_error("Failed to set app metadata creator: {}\n", SDL_GetError());

        if (!copyright_.empty())
            if (SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_COPYRIGHT_STRING, copyright_.c_str()))
                box::println_error("Failed to set app metadata copyright: {}\n", SDL_GetError());

        if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)) {
            box::println_error("Failed to initialize SDL - {}\n", SDL_GetError());
            exit(1);
        }

        if (!TTF_Init()) {
            box::println_error("Failed to initialize TTF - {}\n", SDL_GetError());
            exit(2);
        }
        // displays();
    }


    Application::~Application() {
        delete window_;
        window_ = nullptr;

        TTF_Quit();
        SDL_Quit();
    }

    void Application::run() noexcept {
        window_->prepare();
        window_->show();
        // window_->update_geometry();
        main_loop();
    }

    /****************************************************************
    *                                                               *
    *                     m a i n _ l o o p                         *
    *                                                               *
    ****************************************************************/

    void Application::main_loop() noexcept {
        int n = 0;
        bool quit{};
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    // Window Events --------------------------------
                    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                        // box::print("{}\n", event::to_string(event.type));
                        break;
                    case SDL_EVENT_QUIT:
                        // box::print("{}\n", event::to_string(event.type));
                        if (!can_exit())
                            continue;
                        quit = true;
                        break;
                    case SDL_EVENT_WINDOW_MINIMIZED:
                        // box::print("{}\n", event::to_string(event.type));
                        window_->set_visible(false);
                        break;
                    case SDL_EVENT_WINDOW_RESTORED:
                        // box::print("{}\n", event::to_string(event.type));
                        window_->set_visible(true);
                        break;
                    case SDL_EVENT_WINDOW_MOVED: {
                        // auto e = event.window;
                        // auto x = e.data1;
                        // auto y = e.data2;
                        // box::println("{}, {}", x, y);
                        break;
                    }


                    // Mouse Events ---------------------------------
                    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                        MouseEvent mouse_event{event.button};
                        // box::println("Mouse button down: {}", mouse_event);
                        auto const [x,y] = mouse_event.pos();
                        if (auto const widget = window_->contains_point(x, y)) {
                            box::println_ptr(widget, "Application::Button down event");
                            if (mouse_event.clicks() == 1) widget->mouse_down(mouse_event);
                            else if (mouse_event.clicks() == 2) widget->mouse_double_down(mouse_event);
                        }
                        ++n;
                        break;
                    }
                    case SDL_EVENT_MOUSE_BUTTON_UP: {
                        MouseEvent mouse_event{event.button};
                        auto const [x,y] = mouse_event.pos();
                        if (auto const widget = window_->contains_point(x, y)) {
                            if (mouse_event.clicks() == 1) widget->mouse_up(mouse_event);
                            else if (mouse_event.clicks() == 2) widget->mouse_double_up(mouse_event);
                        }
                        break;
                    }
                    case SDL_EVENT_MOUSE_MOTION: {
                        SDL_MouseMotionEvent const e = event.motion;
                        EventController::self().send(UserEvent::MouseMove, std::pair{e.x, e.y});
                        break;
                    }

                    default: {}
                }
            }
            update();
        }

    }

    void Application::update() {
        while (SDL_GetTicks() < (tick_counter_ + DEADLINE)) {}
        tick_counter_ = SDL_GetTicks();
        window_->draw();
    }

    bool Application::can_exit() const noexcept {
        return window_->can_close();
    }

    void Application::displays() {
        box::println("Available displays:");
        int count = 0;
        SDL_DisplayID* ptr = SDL_GetDisplays(&count);
        for (int i = 0; i < count; i++) {
            auto id = ptr[i];
            auto const name = std::string(SDL_GetDisplayName(id)).c_str();
            SDL_Rect rect;
            SDL_GetDisplayBounds(id, &rect);
            SDL_Rect available;
            SDL_GetDisplayUsableBounds(id, &available);
            box::print("\t id: {}, name: {}, bounds: ({}, {}, {}, {}), usable: ({}, {}, {}, {})\n",
                id, name,
                rect.x, rect.y, rect.w, rect.h,
                available.x, available.y, available.w, available.h);
        }

        SDL_free(ptr);
    }
}
