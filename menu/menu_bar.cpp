//
// Created by piotr on 08.02.25.
//

#include "menu_bar.h"
#include "menu_button.h"
#include "../types.h"
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
        const auto button = new MenuButton(label, this);
        button->set_visible_frame(false);
        button->padding() = {.left = 0, .top = 3, .right = 0, .bottom = 3};
        buttons_.push_back(button);
    }

    Size MenuBar::size_min() const noexcept {
        Size min{};
        for (auto const& button : buttons_) {
            if (button->visible()) {
                auto const [w, h] = button->size_min();
                min.w += w;
                min.h = std::max(min.h, h);
            }
            // 3 pixels gap between buttons
            min.w += static_cast<int>(buttons_.size() - 1);
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
            x += 0;
        }
    };

    Size MenuBar::size_max() const noexcept {
        return frame().size;
    }


    Object *MenuBar::contains_point(f32 const x, f32 const y) noexcept {
        if (frame().contains_point(x, y)) {
            for (auto const& button : buttons_)
                if (button->contains_point(x, y))
                    return button;
            return this;
        }
        return nullptr;
    }

    void MenuBar::mouse_down(MouseEvent event) noexcept {}
    void MenuBar::mouse_up(MouseEvent event) noexcept {}
    void MenuBar::mouse_double_down(MouseEvent event) noexcept {}
    void MenuBar::mouse_double_up(MouseEvent event) noexcept {}

    void MenuBar::update() noexcept {};

    void MenuBar::draw() noexcept {
        draw::fill_rect(renderer(), frame(), thema::DEFAULT_MENU_BACKGROUND);

        for (auto const& button : buttons_)
            button->draw();
        // for (auto const& child : children()) {
        //     child->draw();
        // }
    };

}