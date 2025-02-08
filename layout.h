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

    class HBoxLayout final : public Layout {
    public:
        explicit HBoxLayout(Object* parent = nullptr) : Layout(parent) {}
        void update() noexcept override;
        ~HBoxLayout() override = default;

        void prepare() noexcept override;
        void update_geometry() noexcept override {};
        void draw() noexcept override {};
        [[nodiscard]] Size size_min() const noexcept override { return Size(0, 0); };
        [[nodiscard]] Size size_max() const noexcept override { return Size(0, 0); };
    };

    class VBoxLayout final : public Layout {
    public:
        explicit VBoxLayout(Object* parent = nullptr) : Layout(parent) {}
        void update() noexcept override;
        ~VBoxLayout() override = default;

        void prepare() noexcept override {};
        void update_geometry() noexcept override {};
        void draw() noexcept override {};
        Size size_min() const noexcept override { return Size(0, 0); }
        Size size_max() const noexcept override { return Size(0, 0); }
    };

    class GridLayout final : public Layout {
    public:
        explicit GridLayout(Object* parent = nullptr) : Layout(parent) {}
        void update() noexcept override;
        ~GridLayout() override = default;

        void prepare() noexcept override {};
        void update_geometry() noexcept override {};
        void draw() noexcept override {};
        [[nodiscard]] Size size_min() const noexcept override { return Size(0, 0); };
        [[nodiscard]] Size size_max() const noexcept override { return Size(0, 0); };
    };

}
