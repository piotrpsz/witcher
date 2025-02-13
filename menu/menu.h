//
// Created by piotr on 11.02.25.
//

#pragma once
#include <functional>

#include "../widget.h"

namespace Witcher {
    class MenuButton;

    class Menu final : public Widget {
        std::vector<MenuButton*> buttons_{};
        MenuButton* active_menu_button_{};
    public:
        explicit Menu(Widget* parent);
        ~Menu() override = default;

        void add(std::string_view name, std::function<void()> const& action);

        [[nodiscard]] Size size_min() const noexcept override;
        [[nodiscard]] Size size_max() const noexcept override;
        void draw() noexcept override;
        void update() noexcept override;
        void prepare() noexcept override;;
        void update_geometry() noexcept override;
    };

}