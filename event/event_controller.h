//
// Created by piotr on 10.02.25.
//
#pragma once

#include "../object.h"
#include "../toolbox/all.h"
#include "event.h"
#include <unordered_map>
#include <unordered_set>
#include <mutex>

namespace Witcher {

    class EventController {
        using Store = std::unordered_map<uint, std::unordered_set<Object*>>;
        Store store_{};
        std::mutex mutex_{};
    public:
        // singleton
        static EventController& self() {
            static EventController self_;
            return self_;
        }
        // no copy, no move
        EventController(EventController const&) = delete;
        EventController(EventController&&) = delete;
        EventController& operator=(EventController const&) = delete;
        EventController& operator=(EventController&&) = delete;
        ~EventController() = default;

        /// Append a subscriber who is interested in receiving user events with the specified IDs.
        /// \param subscriber to append,
        /// \param ids Numbers which are IDs of events.
        template<typename... T>
        void append(Object* const subscriber, T const... ids) {
            std::lock_guard<std::mutex> lg(mutex_);

            auto add = [&](Object* const s, uint const id) {
                if (auto const exists = store_.contains(id) && store_[id].contains(s); !exists)
                    store_[id].insert(s);
            };

            (..., add(subscriber, ids));
        }

        /// The specified subscriber no longer want to follow the events.
        /// \param subscriber to remove.
        void remove(Object* const subscriber) {
            std::lock_guard<std::mutex> lg(mutex_);

            std::vector<uint> keys_to_remove{};
            for (auto& [k, v] : store_) {
                v.erase(subscriber);
                if (v.empty()) keys_to_remove.push_back(k);
            }
            for (auto const id : keys_to_remove)
                store_.erase(id);
        }

        template<typename... T>
        void send(uint const id, T const... args) {
            std::lock_guard<std::mutex> lg(mutex_);

            if (store_.contains(id)) {
                if (auto const& subscribers = store_[id]; !subscribers.empty()) {
                    UserEvent const event(id, args...);
                    for (auto const& obj : subscribers)
                        obj->user_event(event);
                }
            }
        }

        void print_content() const noexcept {
            if (store_.empty()) {
                return;
            }
            for (auto const& [k, v] : store_) {
                bee::box::print("\t {} : ", k);
                for (auto const obj : v)
                    bee::box::print("{}, ", static_cast<void *>(obj));
                bee::box::println("");
            }
        }

    private:
        EventController() = default;
    };

}

