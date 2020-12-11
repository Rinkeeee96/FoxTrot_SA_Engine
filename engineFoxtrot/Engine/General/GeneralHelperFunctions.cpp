#include "stdafx.h"
namespace {
    /// @brief Calculate Degrees to Radians
    /// @param a 
    /// @return 
    float Degree2Radians(float a)
    {
        return a * DEGREE2RADIANS;
    }

    /// @brief Calculate Radians to Degrees
    /// @param a 
    /// @return 
    float Radians2Degree(float a)
    {
        return a * RADIANS2DEGREE;
    }

    /// @brief Checks if value is between min and max. Otherwise return the min or max.
    /// @param value 
    /// @param min_inclusive 
    /// @param max_inclusive 
    /// @return 
    float clampf(float value, float min_inclusive, float max_inclusive)
    {
        if (min_inclusive > max_inclusive)
        {
            std::swap(min_inclusive, max_inclusive);
        }
        return value < min_inclusive ? min_inclusive : value < max_inclusive ? value : max_inclusive;
    }

    /// @brief A more effective random number generator
    /// @param seed 
    /// @return 
    static float RANDOM_M11(unsigned int* seed)
    {
        *seed = *seed * 134775813 + 1;
        union
        {
            uint32_t d;
            float f;
        } u;
        u.d = (((uint32_t)(*seed) & 0x7fff) << 8) | 0x40000000;
        return u.f - 3.0f;
    }
}