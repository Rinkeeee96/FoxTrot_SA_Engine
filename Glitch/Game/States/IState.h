#pragma once

template <typename T>
class IState
{
public:
    virtual ~IState() = default;

    virtual void entry(T* entity) = 0;
    virtual void execute(T* entity) = 0;
    virtual void exit(T* entity) = 0;
};