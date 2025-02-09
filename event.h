//
// Created by piotr on 05.02.25.
//

#pragma once

#include <string>
#include <unordered_map>

namespace Witcher {
    class event {
        static std::unordered_map<int, char const* const> data_;
    public:
        static std::string to_string(uint id);
    };
}
