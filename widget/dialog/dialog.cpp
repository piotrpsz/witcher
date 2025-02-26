//
// Created by piotr on 26.02.25.
//

#include "dialog.h"
#include <SDL3/SDL.h>

#include "../../toolbox/toolbox.h"
#include "../../toolbox/crypto/blowfish/blowfish.h"


bool Witcher::Dialog::show(std::string const& title, std::string const& message, SDL_Window* const window) noexcept {
    if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), window))
        return true;
    bee::box::println_error("SDL_ShowSimpleMessageBox: {} ", SDL_GetError());
    return {};
}
