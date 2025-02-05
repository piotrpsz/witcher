//
// Created by piotr on 05.02.25.
//

/*------- include files:
-------------------------------------------------------------------*/
#include "application.h"
#include "types.h"
#include "toolbox/all.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "window.h"

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

        if (!app_creator.empty())
            if (!SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING, creator_.c_str()))
                box::println_error("Failed to set app metadata creator: {}\n", SDL_GetError());

        if (!app_copyright.empty())
            if (!SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_COPYRIGHT_STRING, copyright_.c_str()))
                box::println_error("Failed to set app metadata copyright: {}\n", SDL_GetError());

        if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)) {
            box::println_error("Failed to initialize SDL - {}\n", SDL_GetError());
            exit(1);
        }

        if (!TTF_Init()) {
            box::println_error("Failed to initialize TTF - {}\n", SDL_GetError());
            exit(2);
        }
    }


    Application::~Application() {
        for (auto win : windows_)
            win.reset();

        TTF_Quit();
        SDL_Quit();
    }

    void Application::add_child(std::shared_ptr<Window> win) noexcept {
        windows_.push_back(std::move(win));
    }

    void Application::run() noexcept {
        main_loop();
    }

    void Application::main_loop() noexcept {
        for (auto const win : windows_)
            win->show();



    }

}
