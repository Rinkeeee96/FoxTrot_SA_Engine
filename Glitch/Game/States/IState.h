#pragma once

template <typename T>
class IState
{
public:
    virtual ~IState() = default;

    /// @brief 
    /// entry
    virtual void entry(T* entity) = 0;
    /// @brief 
    /// execute
    virtual void execute(T* entity) = 0;
    /// @brief 
    /// on exit
    virtual void exit(T* entity) = 0;
};