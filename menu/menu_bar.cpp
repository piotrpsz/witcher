//
// Created by piotr on 08.02.25.
//

#include "menu_bar.h"
#include "../types.h"
#include "../button.h"
#include "../toolbox/all.h"
#include "../helpers/draw.h"
#include "../thema.h"
#include <numeric>

namespace Witcher {
    using namespace bee;

    MenuBar::MenuBar(Widget *parent) : Widget(ObjectType::MenuBar, parent) {
        set_parent(parent);
        set_visible(true);
        set_visible_frame(false);
        set_resizeable(true);
    }

    MenuBar::~MenuBar() {
        box::println("MenuBar::~MenuBar");
    }

    void MenuBar::add(std::string const& label) noexcept {
        auto button = new Button(label, this);
        button->set_visible_frame(false);
        button->padding().left = 0;
        button->padding().right = 0;
        button->padding().top = 2;
        button->padding().bottom = 2;
        buttons_.push_back(std::move(button));
    }

    /*
    *        auto const n = std::accumulate(
                text.cbegin(),
                text.cend(),
                size_t{},
                [delimiter](int const count, char const c) {
                    return c == delimiter ? count + 1 : count;
                }
            );
    */
    Size MenuBar::size_min() const noexcept {
        Size min{};
        for (auto const& button : buttons_) {
            if (button->visible()) {
                auto const [w, h] = button->size_min();
                min.w += w;
                min.h = std::max(min.h, h);
            }
            // 3 pixels gap between buttons
            min.w += 3 * static_cast<int>(buttons_.size() - 1);
            return {min.w, min.h};
        }
        return min;
    }

    void MenuBar::prepare() noexcept {
        for (auto const& button : buttons_)
            button->prepare();

        auto frame = parent()->frame();
        auto [w, h] = size_min();
        frame.pos = {};
        frame.size.h = h;
        set_frame(frame);

        update_geometry();
    };

    void MenuBar::update_geometry() noexcept {
        auto x = 1;
        for (auto const& button : buttons_) {
            button->move(x, 0);
            x += button->size_min().w;
            x += 3;
        }
    };

    Size MenuBar::size_max() const noexcept {}

    void MenuBar::mouse_down(MouseEvent event) noexcept {}
    void MenuBar::mouse_up(MouseEvent event) noexcept {}
    void MenuBar::mouse_double_down(MouseEvent event) noexcept {}
    void MenuBar::mouse_double_up(MouseEvent event) noexcept {}

    void MenuBar::update() noexcept {};

    void MenuBar::draw() noexcept {
        draw::fill_rect(renderer(), frame(), thema::DEFAULT_MENU_BACKGROUND);

        for (auto const& button : buttons_)
            button->draw();
    };

}