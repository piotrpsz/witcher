//
// Created by piotr on 11.02.25.
//

#pragma once
#include <functional>
#include "../widgets/button/action.h"
#include "../widgets/widget/widget.h"

namespace Witcher {
    class MenuButton;

    class Menu final : public Widget {
        std::vector<MenuButton*> buttons_{};
        MenuButton* active_menu_button_{};
        bool has_submenu_{};
    public:
        explicit Menu(Widget* parent);
        ~Menu() noexcept override;

        /// Adding a menu button to the menu.
        /// \param text Text displayed in the button.
        /// \param action Action performed after pressing the button (if given).
        /// \return Pointer to the created button
        MenuButton* add(std::string text, Action action = {});



        void refocus(std::pair<f32, f32> const& point) noexcept;

        Object* contains_point(std::pair<f32, f32> point) noexcept override;
        [[nodiscard]] Size size_min() const noexcept override;
        [[nodiscard]] Size size_max() const noexcept override;
        void draw() noexcept override;
        void update() noexcept override;
        void prepare() noexcept override;;
        void update_geometry() noexcept override;
        void deactivate() noexcept override;
    };

}