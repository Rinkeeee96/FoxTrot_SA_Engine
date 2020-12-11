#pragma once
/// @brief Interface class for global state
/// @tparam T 
template <typename T>
class IGlobalState
{
public:
    /// @brief 
    /// execute
    virtual void execute(T* entity) = 0;
};
