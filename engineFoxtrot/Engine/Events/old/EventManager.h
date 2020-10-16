#pragma once

#include "EventType.h"
#include "EventListener.h"
#include "../SceneManager/Object.h"

#if(EXPORT)
class DLLEXPORT EventManager
#else
class EventManager 
#endif
{
private:
    std::map<const EventType, std::vector<EventListener*>> listeners = std::map<const EventType, std::vector<EventListener*>>();
public:
    EventManager() { }

    void subscribe(const EventType eventType, EventListener* listener);
    void unsubscribe(const EventType eventType, EventListener* listener);
    void notify(const EventType eventType, Object* data);
};