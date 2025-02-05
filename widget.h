//
// Created by piotr on 30.01.25.
//

#pragma once

#include "types.h"
#include "object.h"

namespace Witcher {

    class Widget : public Object {

    public:
        explicit Widget(ObjectType const type, Object *parent = nullptr) : Object(type, parent) {
            // The assumption is that each widget has focus by default.
            // If a widget is not to have focus, it must be set in a derived class.
            set_focusable(true);
            // By default, the widget has no focus.
            // Focus must be set explicitly.
            set_focus(false);
            // By default, the widget should be displayable.
            set_displayable(true);
        }
    };

}
