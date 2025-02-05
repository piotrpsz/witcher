//
// Created by piotr on 02.02.25.
//

#include "object.h"

namespace Witcher {

    Object::~Object() {
        for (auto&& child : children_) {
            child->close();
            delete child;
        }
    }

    Object* Object::contains_point(f32 const x, f32 const y) noexcept {
        if (focusable() && frame_.contains_point(x, y)) {
            for (auto const& child : children_) {
                if (child->contains_point(x, y))
                    return child;
            }
            return this;
        }
        return {};
    }

    void Object::set_frame(Rect const frame) noexcept {
        frame_ = frame;
        update_area(frame);
    }

    void Object::update_area(Rect const frame) noexcept {
        area_.pos.x = frame.pos.x + padding_.left;
        area_.pos.y = frame.pos.y + padding_.top;
        area_.size.w = frame.size.w - padding_.left - padding_.right;
        area_.size.h = frame.size.h - padding_.top - padding_.bottom;
    }

    void Object::set_area(Rect const area) noexcept {
        area_ = area;
        // frame_.pos.x = area_.pos.x - padding_.left;
        // frame_.pos.y = area_.pos.y - padding_.top;
        frame_.size.w = area.size.w + padding_.left + padding_.right;
        frame_.size.h = area.size.h + padding_.top + padding_.bottom;
    }

    void Object::set_pos(int const x, int const y) noexcept {
        auto const dx = x - frame_.pos.x;
        auto const dy = y - frame_.pos.y;
        move(dx, dy);
    }

    void Object::move(int const dx, int const dy) noexcept {
        frame_.move(dx, dy);
        update_area(frame_);
        for (auto const& child : children_) {
            child->move(dx, dy);
        }
    }

}
