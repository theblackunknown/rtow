#pragma once

#include <cmath>

namespace rtow {
inline float sqrt( float v )
{
    return std::sqrt( v );
}

inline float abs( float a )
{
    return a < 0.f ? -a : a;
}

inline float min( float a, float b )
{
    return a < b ? a : b;
}

inline float max( float a, float b )
{
    return a > b ? a : b;
}

inline float clamp( float x, float min, float max )
{
    if ( x < min )
        return min;
    if ( x > max )
        return max;
    return x;
}
}  // namespace rtow
