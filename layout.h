//
// Created by piotr on 30.01.25.
//

#pragma once

#include "object.h"

namespace Witcher {

    class Layout : public Object {
    public:
        explicit Layout(Object* parent = nullptr) : Object(ObjectType::Layout, parent) {}
        ~Layout() override = default;
    };

    class HBoxLayout : public Layout {
    public:
        explicit HBoxLayout(Object* parent = nullptr) : Layout(parent) {}
        void update() noexcept override;
        ~HBoxLayout() override = default;
    };

    class VBoxLayout : public Layout {
    public:
        explicit VBoxLayout(Object* parent = nullptr) : Layout(parent) {}
        void update() noexcept override;
        ~VBoxLayout() override = default;
    };

    class GridLayout : public Layout {
    public:
        explicit GridLayout(Object* parent = nullptr) : Layout(parent) {}
        void update() noexcept override;
        ~GridLayout() override = default;
    };

}
