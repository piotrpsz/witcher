//
// Created by piotr on 05.02.25.
//

/*------- include files:
-------------------------------------------------------------------*/
#include "application.h"
#include "window.h"
#include "sdl_event.h"
#include "toolbox/all.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "event/event_controller.h"
#include <unordered_map>

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
        box::println("Application::Application");
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
        displays();
        // window_->update_geometry();
        main_loop();
    }

    /****************************************************************
    *                                                               *
    *                     m a i n _ l o o p                         *
    *                                                               *
    ****************************************************************/

    void Application::main_loop() noexcept {
        bool quit{};
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    // Window Events --------------------------------
                    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                        // box::print("{}\n", sdl_event::to_string(event.type));
                        break;
                    case SDL_EVENT_QUIT:
                        // box::print("{}\n", sdl_event::to_string(event.type));
                        if (!can_exit())
                            continue;
                        quit = true;
                        break;
                    case SDL_EVENT_WINDOW_MINIMIZED:
                        // box::print("{}\n", sdl_event::to_string(event.type));
                        window_->set_visible(false);
                        break;
                    case SDL_EVENT_WINDOW_RESTORED:
                        // box::print("{}\n", sdl_event::to_string(event.type));
                        window_->set_visible(true);
                        break;
                    case SDL_EVENT_WINDOW_MOVED:
                        break;
                    case SDL_EVENT_WINDOW_RESIZED:
                        // box::print("{}\n", sdl_event::to_string(event.type));
                        window_->update_geometry();
                        break;

                    // Mouse Events ---------------------------------
                    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                        // box::print("{}\n", sdl_event::to_string(event.type));
                        MouseEvent mouse_event{event.button};
                        if (auto const widget = window_->contains_point(mouse_event.pos())) {
                            if (mouse_event.clicks() == 1) widget->mouse_down(mouse_event);
                            else if (mouse_event.clicks() == 2) widget->mouse_double_down(mouse_event);
                        }
                        break;
                    }
                    case SDL_EVENT_MOUSE_BUTTON_UP: {
                        MouseEvent mouse_event{event.button};
                        if (auto const widget = window_->contains_point(mouse_event.pos())) {
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

    std::string Application::pixel_format(SDL_PixelFormat const pixfmt) noexcept {
        static const std::unordered_map<SDL_PixelFormat, char const* const> formats = {
            { SDL_PIXELFORMAT_INDEX1LSB    , "SDL_PIXELFORMAT_INDEX1LSB"   },
            { SDL_PIXELFORMAT_INDEX1MSB    , "SDL_PIXELFORMAT_INDEX1MSB"   },
            { SDL_PIXELFORMAT_INDEX2LSB    , "SDL_PIXELFORMAT_INDEX2LSB"   },
            { SDL_PIXELFORMAT_INDEX2MSB    , "SDL_PIXELFORMAT_INDEX2MSB"   },
            { SDL_PIXELFORMAT_INDEX4LSB    , "SDL_PIXELFORMAT_INDEX4LSB"   },
            { SDL_PIXELFORMAT_INDEX4MSB    , "SDL_PIXELFORMAT_INDEX4MSB"   },
            { SDL_PIXELFORMAT_INDEX8       , "SDL_PIXELFORMAT_INDEX8"      },
            { SDL_PIXELFORMAT_RGB332       , "SDL_PIXELFORMAT_RGB332"      },
            { SDL_PIXELFORMAT_XRGB4444     , "SDL_PIXELFORMAT_XRGB4444"    },
            { SDL_PIXELFORMAT_XRGB1555     , "SDL_PIXELFORMAT_XRGB1555"    },
            { SDL_PIXELFORMAT_XBGR1555     , "SDL_PIXELFORMAT_XBGR1555"    },
            { SDL_PIXELFORMAT_ARGB4444     , "SDL_PIXELFORMAT_ARGB4444"    },
            { SDL_PIXELFORMAT_RGBA4444     , "SDL_PIXELFORMAT_RGBA4444"    },
            { SDL_PIXELFORMAT_ABGR4444     , "SDL_PIXELFORMAT_ABGR4444"    },
            { SDL_PIXELFORMAT_BGRA4444     , "SDL_PIXELFORMAT_BGRA4444"    },
            { SDL_PIXELFORMAT_ARGB1555     , "SDL_PIXELFORMAT_ARGB1555"    },
            { SDL_PIXELFORMAT_XBGR4444     , "SDL_PIXELFORMAT_XBGR4444"    },
            { SDL_PIXELFORMAT_RGBA5551     , "SDL_PIXELFORMAT_RGBA5551"    },
            { SDL_PIXELFORMAT_ABGR1555     , "SDL_PIXELFORMAT_ABGR1555"    },
            { SDL_PIXELFORMAT_BGRA5551     , "SDL_PIXELFORMAT_BGRA5551"    },
            { SDL_PIXELFORMAT_RGB565       , "SDL_PIXELFORMAT_RGB565"      },
            { SDL_PIXELFORMAT_BGR565       , "SDL_PIXELFORMAT_BGR565"      },
            { SDL_PIXELFORMAT_RGB24        , "SDL_PIXELFORMAT_RGB24"       },
            { SDL_PIXELFORMAT_BGR24        , "SDL_PIXELFORMAT_BGR24"       },
            { SDL_PIXELFORMAT_XRGB8888     , "SDL_PIXELFORMAT_XRGB8888"    },
            { SDL_PIXELFORMAT_RGBX8888     , "SDL_PIXELFORMAT_RGBX8888"    },
            { SDL_PIXELFORMAT_XBGR8888     , "SDL_PIXELFORMAT_XBGR8888"    },
            { SDL_PIXELFORMAT_BGRX8888     , "SDL_PIXELFORMAT_BGRX8888"    },
            { SDL_PIXELFORMAT_ARGB8888     , "SDL_PIXELFORMAT_ARGB8888"    },
            { SDL_PIXELFORMAT_RGBA8888     , "SDL_PIXELFORMAT_RGBA8888"    },
            { SDL_PIXELFORMAT_ABGR8888     , "SDL_PIXELFORMAT_ABGR8888"    },
            { SDL_PIXELFORMAT_BGRA8888     , "SDL_PIXELFORMAT_BGRA8888"    },
            { SDL_PIXELFORMAT_XRGB2101010  , "SDL_PIXELFORMAT_XRGB2101010" },
            { SDL_PIXELFORMAT_XBGR2101010  , "SDL_PIXELFORMAT_XBGR2101010" },
            { SDL_PIXELFORMAT_ARGB2101010  , "SDL_PIXELFORMAT_ARGB2101010" },
            { SDL_PIXELFORMAT_ABGR2101010  , "SDL_PIXELFORMAT_ABGR2101010" },
            { SDL_PIXELFORMAT_RGB48        , "SDL_PIXELFORMAT_RGB48"       },
            { SDL_PIXELFORMAT_BGR48        , "SDL_PIXELFORMAT_BGR48"       },
            { SDL_PIXELFORMAT_RGBA64       , "SDL_PIXELFORMAT_RGBA64"      },
            { SDL_PIXELFORMAT_ARGB64       , "SDL_PIXELFORMAT_ARGB64"      },
            { SDL_PIXELFORMAT_BGRA64       , "SDL_PIXELFORMAT_BGRA64"      },
            { SDL_PIXELFORMAT_ABGR64       , "SDL_PIXELFORMAT_ABGR64"      },
            { SDL_PIXELFORMAT_RGB48_FLOAT  , "SDL_PIXELFORMAT_RGB48_FLOAT" },
            { SDL_PIXELFORMAT_BGR48_FLOAT  , "SDL_PIXELFORMAT_BGR48_FLOAT" },
            { SDL_PIXELFORMAT_RGBA64_FLOAT , "SDL_PIXELFORMAT_RGBA64_FLOAT" },
            { SDL_PIXELFORMAT_ARGB64_FLOAT , "SDL_PIXELFORMAT_ARGB64_FLOAT" },
            { SDL_PIXELFORMAT_BGRA64_FLOAT , "SDL_PIXELFORMAT_BGRA64_FLOAT" },
            { SDL_PIXELFORMAT_ABGR64_FLOAT , "SDL_PIXELFORMAT_ABGR64_FLOAT" },
            { SDL_PIXELFORMAT_RGB96_FLOAT  , "SDL_PIXELFORMAT_RGB96_FLOAT"  },
            { SDL_PIXELFORMAT_BGR96_FLOAT  , "SDL_PIXELFORMAT_BGR96_FLOAT"  },
            { SDL_PIXELFORMAT_RGBA128_FLOAT, "SDL_PIXELFORMAT_RGBA128_FLOAT" },
            { SDL_PIXELFORMAT_ARGB128_FLOAT, "SDL_PIXELFORMAT_ARGB128_FLOAT" },
            { SDL_PIXELFORMAT_BGRA128_FLOAT, "SDL_PIXELFORMAT_BGRA128_FLOAT" },
            { SDL_PIXELFORMAT_ABGR128_FLOAT, "SDL_PIXELFORMAT_ABGR128_FLOAT" },
            { SDL_PIXELFORMAT_YV12         , "SDL_PIXELFORMAT_YV12"          },
            { SDL_PIXELFORMAT_IYUV         , "SDL_PIXELFORMAT_IYUV"          },
            { SDL_PIXELFORMAT_YUY2         , "SDL_PIXELFORMAT_YUY2"          },
            { SDL_PIXELFORMAT_UYVY         , "SDL_PIXELFORMAT_UYVY"          },
            { SDL_PIXELFORMAT_YVYU         , "SDL_PIXELFORMAT_YVYU"          },
            { SDL_PIXELFORMAT_NV12         , "SDL_PIXELFORMAT_NV12"          },
            { SDL_PIXELFORMAT_NV21         , "SDL_PIXELFORMAT_NV21"          },
            { SDL_PIXELFORMAT_P010         , "SDL_PIXELFORMAT_P010"          },
            { SDL_PIXELFORMAT_EXTERNAL_OES , "SDL_PIXELFORMAT_EXTERNAL_OES"  },
            { SDL_PIXELFORMAT_MJPG         , "SDL_PIXELFORMAT_MJPG"          },
        };
        static const std::unordered_map<SDL_PixelFormat, char const* const> aliases = {
            { SDL_PIXELFORMAT_RGBA32       , "SDL_PIXELFORMAT_RGBA32"        },
            { SDL_PIXELFORMAT_ARGB32       , "SDL_PIXELFORMAT_ARGB32"        },
            { SDL_PIXELFORMAT_BGRA32       , "SDL_PIXELFORMAT_BGRA32"        },
            { SDL_PIXELFORMAT_ABGR32       , "SDL_PIXELFORMAT_ABGR32"        },
            { SDL_PIXELFORMAT_RGBX32       , "SDL_PIXELFORMAT_RGBX32"        },
            { SDL_PIXELFORMAT_XRGB32       , "SDL_PIXELFORMAT_XRGB32"        },
            { SDL_PIXELFORMAT_BGRX32       , "SDL_PIXELFORMAT_BGRX32"        },
            { SDL_PIXELFORMAT_XBGR32       , "SDL_PIXELFORMAT_XBGR32"        },
        };

        if (auto const it = formats.find(pixfmt); it != formats.end()) {
            if (auto const ait = aliases.find(pixfmt); ait != aliases.end())
                return std::format("{} / {}", ait->second, it->second);
            return it->second;
        }
        return "SDL_PIXELFORMAT_UNKNOWN";
    }

    void Application::displays() {
        box::println("Available displays:");
        int count = 0;
        SDL_DisplayID* ptr = SDL_GetDisplays(&count);
        for (int i = 0; i < count; i++) {
            auto const id = ptr[i];
            auto const name = std::string(SDL_GetDisplayName(id)).c_str();
            SDL_Rect rect;
            SDL_GetDisplayBounds(id, &rect);
            SDL_Rect available;
            SDL_GetDisplayUsableBounds(id, &available);
            box::print("\t id: {}, name: {}, bounds: ({}, {}, {}, {}), usable: ({}, {}, {}, {})\n",
                id, name,
                rect.x, rect.y, rect.w, rect.h,
                available.x, available.y, available.w, available.h);
            auto const mode = SDL_GetDesktopDisplayMode(id);
            if (!mode) continue;
            box::println("\t\t pixel density: {}, refresh rate: {}, pixel: {}",
                mode->pixel_density, mode->refresh_rate, pixel_format(mode->format));
        }

        SDL_free(ptr);
    }
}
