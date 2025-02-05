//
// Created by piotr on 03.02.25.
//

#include "font.h"
#include "toolbox/toolbox.h"
#include <format>

#include "toolbox/file.h"
#include "toolbox/crypto/crypto.h"

// https://wiki.libsdl.org/SDL3_ttf/CategoryAPI

namespace Witcher {
    using namespace bee;

    static std::vector<unsigned char> passwd {
        0x8d, 0x12, 0x77, 0x46, 0xc5, 0x1e, 0xd6, 0x66, 0xde, 0xa7,
        0xb6, 0xaf, 0x8d, 0x45, 0xce, 0xef, 0x7f, 0xfd, 0xc7, 0xc0,
        0xd3, 0x21, 0x5f, 0xf3, 0xb0, 0x02, 0x0f, 0xc8, 0x57, 0xd4,
        0xb6, 0x6e, 0x26, 0x81, 0x6e, 0xa8, 0xbe, 0x36, 0xd5, 0xf2,
        0x0c, 0xb1, 0x97, 0xf8, 0x97, 0x36, 0x08, 0xa8, 0xb9, 0xc9,
        0x97, 0x82, 0xc8, 0xa7, 0x17, 0xb3};


    /****************************************************************
    *                                                               *
    *                     C O N S T R U C T O R                     *
    *                                                               *
    ****************************************************************/

    Font::Font(std::string_view const name, f32 const size) {
        auto const file_path = std::format("{}/.witcher/{}.bin", bee::box::home_dir(), name);
        if (auto const ttf_bytes = bee::file::read_binary(file_path)) {
            bee::crypto::blowfish const bf(passwd);
            auto const decrypted = bf.decrypt_ecb(ttf_bytes.value());
            auto const decompressed = bee::box::decompress(decrypted);

            if (auto const stream = SDL_IOFromConstMem(decompressed.data(), decompressed.size())) {
                if (auto const font = TTF_OpenFontIO(stream, true, size)) {
                    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
                    font_ = font;
                    return;
                }
            }
        }
        bee::box::print_error("Failed to load font {} in size {}: {}\n", name, size, SDL_GetError());
    }

    /****************************************************************
    *                                                               *
    *                       g e o m e t r y                         *
    *                                                               *
    ****************************************************************/

    std::optional<Size> Font::geometry(std::string const& text) const noexcept {
        Size size;
        if (TTF_GetStringSize(font_, text.c_str(), text.size(), &size.w, &size.h))
            return size;

        box::print_error("Failed to get text geometry.\n");
        return {};
    }

    /****************************************************************
    *                                                               *
    *                   t e x t u r e _ f o r                       *
    *                                                               *
    ****************************************************************/

    SDL_Texture* Font::texture_for(SDL_Renderer* const renderer, std::string const &text, SDL_Color const color) const noexcept {
        if (auto const surface = TTF_RenderText_Blended(font_, text.c_str(), text.size(), color))
            if (auto const texture = SDL_CreateTextureFromSurface(renderer, surface))
                if (SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST))
                    return texture;

        box::print_error("Failed texture_for: {}\n", SDL_GetError());
        return {};
    }

    /****************************************************************
    *                                                               *
    *                     d e s c r i p t i o n                     *
    *                                                               *
    ****************************************************************/

    void Font::description() const noexcept {
        box::println("Font (");
        box::println("\t font family: {}", TTF_GetFontFamilyName(font_));
        box::println("\t font style : {}", TTF_GetFontStyleName(font_));
        box::println("\t font size: {}", TTF_GetFontSize(font_));
        box::println("\t font ascent: {}", TTF_GetFontAscent(font_));
        box::println("\t font descent: {}", TTF_GetFontDescent(font_));
        int hdpi, vdpi;
        TTF_GetFontDPI(font_, &hdpi, &vdpi);
        box::println("\t font hdpi x vdpi: {}x{}", hdpi, vdpi);
        box::println("\t font height: {} point size", TTF_GetFontHeight(font_));
        box::println("\t font kerning: {}", TTF_GetFontKerning(font_));
        box::println("\t spacing between lines of text: {} ", TTF_GetFontLineSkip(font_));
        box::println("\t outline: {}", TTF_GetFontOutline(font_));
        box::println("\t font style: {} ", style(TTF_GetFontStyle(font_)));
        box::println("\t wrap alignment: {}", alignment(TTF_GetFontWrapAlignment(font_)));
    }

    /****************************************************************
    *                                                               *
    *                          s t y l e                            *
    *                                                               *
    ****************************************************************/

    std::string Font::style(TTF_FontStyleFlags const flags) noexcept {
        if (flags == TTF_STYLE_NORMAL)
            return "normal";

        std::string buffer{};
        if ((flags & TTF_STYLE_BOLD) == TTF_STYLE_BOLD)
            buffer += "bold";
        if ((flags & TTF_STYLE_ITALIC) == TTF_STYLE_ITALIC) {
            if (!buffer.empty()) buffer += " | ";
            buffer += "italic";
        }
        if ((flags & TTF_STYLE_UNDERLINE) == TTF_STYLE_UNDERLINE) {
            if (!buffer.empty()) buffer += " | ";
            buffer += "underline";
        }
        if ((flags & TTF_STYLE_STRIKETHROUGH) == TTF_STYLE_STRIKETHROUGH) {
            if (!buffer.empty()) buffer += " | ";
            buffer += "strikethrough";
        }
        return buffer;
    }

    /****************************************************************
    *                                                               *
    *                       a l i g n m e n t                       *
    *                                                               *
    ****************************************************************/

    std::string Font::alignment(TTF_HorizontalAlignment const flags) noexcept {
        if ((flags & TTF_HORIZONTAL_ALIGN_LEFT) == TTF_HORIZONTAL_ALIGN_LEFT)
            return "left";
        if ((flags & TTF_HORIZONTAL_ALIGN_CENTER) == TTF_HORIZONTAL_ALIGN_CENTER)
            return "center";
        if ((flags & TTF_HORIZONTAL_ALIGN_RIGHT) == TTF_HORIZONTAL_ALIGN_RIGHT)
            return "right";
        return "invalid";
    }

}
