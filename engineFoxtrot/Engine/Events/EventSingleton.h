#pragma once
#include "Event.h"

using EventCallbackFn = function<bool(Event&)>;

#define BIND_EVENT_FN(x) bind(&x, this, placeholders::_1)

class EventSingleton
{
public:
    static API EventSingleton& get_instance() { return instance; }

    // prohibit copy & move
    API EventSingleton(const EventSingleton&) = delete;
    API EventSingleton(EventSingleton&&) = delete;
    API EventSingleton& operator=(const EventSingleton&) = delete;
    API EventSingleton& operator=(EventSingleton&&) = delete;

    /// @brief
    /// OnEvent is triggered when an event is fired, and send message to all registered listiners
    /// @template T is fired
    /// @param Event the event that is fired with data
    /// @assert check wheter the type T and the Event fired is the same
    template<typename T>
    void dispatchEvent(Event& event) {
        static_assert(is_base_of<Event, T>::value, "dispatchEvent Assert fail: Make sure the event that is fired and the Template Type is the same"); 
        string name;
        bool handled = false;
        if (handlerExists<T>(name)) {
            for (auto handler : handlers.at(name)) {
                // TODO how should keypressed events be handled,
                // e.g a key is pressed but 
                if (!handled)
                    handled = handler(event);
                else return;
            }
        }
    }


    // TODO DOXY
    template<typename T>
    void unSubscribe(const EventCallbackFn& callbackToRemove) {
        static_assert(is_base_of<Event, T>::value, "unSubscribe Assert fail: Make sure the event that is fired and the Template Type is the same");
        string name;
        if (handlerExists<T>(name)) {
            for (const EventCallbackFn& registeredCallback : handlers.at(name))
                if (addressof(callbackToRemove) == addressof(registeredCallback))  
                    handlers.erase(name);
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
        if(handlerExists<T>(name)) { 
            handlers[name].push_back(callback);
        }
        // Create new vector
        else {
            handlers[name].push_back({ callback });
        }
    }

private:
    map<string, vector<EventCallbackFn>> handlers = map<string, vector<EventCallbackFn>>();
    static EventSingleton instance;

    template<typename T>
    bool handlerExists(string& name) {
        name = typeid(T).name();
        return handlers.count(name) > 0;
    }

    EventSingleton() {}
};