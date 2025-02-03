//
// Created by piotr on 02.02.25.
//

#pragma once

#include "types.h"
#include "mouse_event.h"
#include <vector>
#include <bitset>
#include <SDL3/SDL.h>

namespace Witcher {

    class Object {
        ObjectType type_{ObjectType::None};
        Rect frame_{};
        Rect area_{};
        Object *parent_{};
        std::vector<Object *> children_{};
        std::bitset<16> flags_{};
        SDL_Renderer *renderer_{};
        Padding padding_{
            .left = DEFAULT_LEFT_PADDING,
            .top = DEFAULT_TOP_PADDING,
            .right = DEFAULT_RIGHT_PADDING,
            .bottom = DEFAULT_BOTTOM_PADDING};
    public:
        explicit Object(Object* const parent = nullptr) : parent_{parent} {}
        virtual ~Object() noexcept;

        // SETTERS
        void set_parent(Object * const parent) noexcept { parent_ = parent; }
        void set_renderer(SDL_Renderer * const renderer) noexcept { renderer_ = renderer; }
        void add_child(Object* const child) noexcept { children_.push_back(child); }

        // GETTERS
        [[nodiscard]] Object* parent() const noexcept { return parent_; }
        [[nodiscard]] ObjectType type() const noexcept { return type_; }
        [[nodiscard]] SDL_Renderer* renderer() const noexcept { return renderer_; }
        [[nodiscard]] Object* contains_point(f32 x, f32 y) noexcept;

        // Iterate over children.
        using iterator = std::vector<Object *>::iterator;
        using const_iterator = std::vector<Object *>::const_iterator;
        iterator begin() { return children_.begin(); }
        iterator end() { return children_.end(); }
        [[nodiscard]] const_iterator cbegin() const { return children_.cbegin(); }
        [[nodiscard]] const_iterator cend() const { return children_.cend(); }

        // Flags
        [[nodiscard]] bool visible() const noexcept { return flags_.test(VISIBLE_BIT); }
        void set_visible(bool const value) noexcept {flags_.set(VISIBLE_BIT, value); }
        [[nodiscard]] bool visible_frane() const noexcept { return flags_.test(VISIBLE_FRAME_BIT); }
        void set_visible_frame(bool const value) noexcept { flags_.set(VISIBLE_FRAME_BIT, value); }
        [[nodiscard]] bool enabled() const noexcept { return flags_.test(ENABLED_BIT); }
        void set_enabled(bool const value) noexcept { flags_.set(ENABLED_BIT, value); }
        [[nodiscard]] bool focusable() const noexcept { return flags_.test(FOCUSABLE_BIT); }
        void set_focusable(bool const value) noexcept { flags_.set(FOCUSABLE_BIT, value); }
        [[nodiscard]] bool focus() const noexcept { return flags_.test(FOCUS_BIT); }
        void set_focus(bool const value) noexcept {
            if (focusable())
                flags_.set(FOCUS_BIT, value);
        }
        [[nodiscard]] bool resizable() const noexcept { return flags_.test(RESIZEABLE_BIT); }
        void set_resizeable(bool const value) noexcept { flags_.set(RESIZEABLE_BIT, value); }

        // Geometry
        void set_frame(Rect frame) noexcept;
        void update_area(Rect frame) noexcept;
        Rect& frame() noexcept { return frame_; }
        [[nodiscard]] Rect const& frane() const noexcept { return frame_; }
        void set_area(Rect area) noexcept;
        [[nodiscard]] Rect const& area() const noexcept { return area_; }
        void set_pos(int x, int y) noexcept;
        void move(int dx, int dy) noexcept;

        // virtual functions
        virtual void close() {}
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual bool can_close() { return true; }
        virtual void mouse_down(MouseEvent&& event) {}
        virtual void mouse_up(MouseEvent&& event) {}
        virtual void mouse_double_down(MouseEvent&& event) {}
        virtual void mouse_double_up(MouseEvent&& event) {}
protected:
        static constexpr int DEFAULT_LEFT_PADDING = 6;
        static constexpr int DEFAULT_RIGHT_PADDING = 6;
        static constexpr int DEFAULT_TOP_PADDING = 6;
        static constexpr int DEFAULT_BOTTOM_PADDING = 6;

        static constexpr int DEFAULT_LEFT_GAP = 2;
        static constexpr int DEFAULT_RIGHT_GAP = 2;
        static constexpr int DEFAULT_TOP_GAP = 2;
        static constexpr int DEFAULT_BOTTOM_GAP = 2;
    private:
        static constexpr auto VISIBLE_BIT = 0;
        static constexpr auto VISIBLE_FRAME_BIT = 1;
        static constexpr auto ENABLED_BIT = 2;
        static constexpr auto FOCUSABLE_BIT = 3;
        static constexpr auto FOCUS_BIT = 4;
        static constexpr auto RESIZEABLE_BIT = 5;
    };

}
