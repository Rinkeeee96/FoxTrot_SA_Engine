#pragma once
template <typename T>
class IGlobalState
{
public:
    virtual void execute(T* entity) = 0;
};
