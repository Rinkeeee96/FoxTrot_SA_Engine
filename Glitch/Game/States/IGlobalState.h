#pragma once
template <typename T>
class IGlobalState
{
public:
    /// @brief 
    /// execute
    virtual void execute(T* entity) = 0;
};
