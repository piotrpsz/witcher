//
// Created by piotr on 04.02.25.
//

#pragma once
#include "font.h"
#include <string>
#include <vector>
#include <memory>

namespace Witcher {

    class FontStore {
        static constexpr auto DEFAULT_FONT_PATH = "/home/piotr/Projects/cpp/tests/sdl_check/fonts/";
        std::vector<std::shared_ptr<Font>> fonts_{};

    public:
        /// Implemented as singleton
        static FontStore& self() noexcept {
            static auto store_ = FontStore();
            return store_;
        }
        /// No Copy
        FontStore(FontStore const&) = delete;
        FontStore& operator=(FontStore const&) = delete;
        /// No Move
        FontStore(FontStore&&) = delete;
        FontStore& operator=(FontStore&&) = delete;

        void clear() const noexcept {
            for (auto font : fonts_)
                font.reset();
        }

        std::shared_ptr<Font> font(std::string const& font_name, float const font_size) {
            // search
            if (auto const font = contains(font_name, font_size))
                return *font;

            // or create when not found.
            if (auto const font = std::make_shared<Font>(font_name, font_size); font->valid()) {
                fonts_.push_back(font);
                return font;
            }
            return {};
        }

    private:
        [[nodiscard]] auto contains(std::string const& name, float const size) const noexcept
            -> std::optional<std::shared_ptr<Font>>
        {
            if (!fonts_.empty())
                for (auto const & font : fonts_)
                    if (font->name() == name && std::fabs(font->size() - size) <= 0.1)
                        return font;

            return {};
        }

        FontStore() = default;
    };
}
