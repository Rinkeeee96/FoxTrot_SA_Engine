#pragma once
#include "core.h"
#include "Event.h"
#include <memory>
#include <functional>
#include <map>

using EventCallbackFn = function<bool(const Event&)>;
#define BIND_EVENT_FN(x) bind(&x, this, placeholders::_1)

class EventDispatcher
{
public:
    EventDispatcher() = default;
    ~EventDispatcher() {}

    /// @brief
    /// OnEvent is triggered when an event is fired, and send message to all registered listiners
    /// @template T is fired
    /// @param Event the event that is fired with data
    /// @assert check wheter the type T and the Event fired is the same
    template<typename T>
    void dispatchEvent(const Event& event) {
        static_assert(is_base_of<Event, T>::value, "dispatchEvent Assert fail: Make sure the event that is fired and the Template Type is the same");
        string name;
        bool handled = false;
        if (handlerExists<T>(name)) {
            for (auto handler : handlers.at(name)) {
                handled = handler(event);
                if (handled) return;
            }
        }
    }

    /// @brief
    /// Register a callback for a specific Event. 
    /// @template T is fired
    /// @param EventCallbackFn& the method that should be executed when an event is fired
    /// @assert check wheter the type T and the Event fired is the same
    template<typename T>
    void setEventCallback(const EventCallbackFn& callback) {
        static_assert(std::is_base_of<Event, T>::value, "setEventCallback Assert fail: Make sure the event in the param of callback is the same as the Template Type");
        // Contains element 
        string name;
        if (handlerExists<T>(name)) {
            handlers[name].push_back(callback);
        }
        // Create new vector
        else {
            handlers[name].push_back({ callback });
        }
    }

private:
    map<string, vector<EventCallbackFn>> handlers;

    template<typename T>
    bool handlerExists(string& name) {
        try {
            name = typeid(T).name();
            return handlers.count(name) > 0;
        }
        catch (...) {
            return false;
        }
    }
};