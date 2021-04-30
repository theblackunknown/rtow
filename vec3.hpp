#pragma once

#include <cmath>

#include <iostream>

namespace rtow {
struct vec3
{
    float e[3];

    float x() const
    {
        return e[0];
    }

    float y() const
    {
        return e[1];
    }

    float z() const
    {
        return e[2];
    }

    vec3 operator-() const
    {
        return { -e[0], -e[1], -e[2] };
    }

    float operator[]( int i ) const
    {
        return e[i];
    }

    float& operator[]( int i )
    {
        return e[i];
    }

    vec3& operator+=( const vec3& v )
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=( const vec3& v )
    {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }
};

using point = vec3;

inline float length_squared( const vec3& v )
{
    return v.x() * v.x() + v.y() * v.y() + v.z() * v.z();
}

inline float length( const vec3& v )
{
    return std::sqrt( length_squared( v ) );
}

inline vec3 operator+( const vec3& lhs, const vec3& rhs )
{
    return { lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() };
}

inline vec3 operator+( const vec3& lhs, float rhs )
{
    return { lhs.x() + rhs, lhs.y() + rhs, lhs.z() + rhs };
}

inline vec3 operator+( float lhs, const vec3& rhs )
{
    return rhs + lhs;
}

inline vec3 operator-( const vec3& lhs, const vec3& rhs )
{
    return { lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() };
}

inline vec3 operator*( const vec3& lhs, const vec3& rhs )
{
    return { lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z() };
}

inline vec3 operator*( const vec3& lhs, float rhs )
{
    return { lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs };
}

inline vec3 operator*( float lhs, const vec3& rhs )
{
    return rhs * lhs;
}

inline vec3 operator/( const vec3& lhs, float rhs )
{
    return { lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs };
}

inline float dot( const vec3& lhs, const vec3& rhs )
{
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

inline vec3 cross( const vec3& lhs, const vec3& rhs )
{
    return { lhs.y() * rhs.z() - lhs.z() * rhs.y(),
             lhs.z() * rhs.x() - lhs.x() * rhs.z(),
             lhs.x() * rhs.y() - lhs.y() * rhs.x() };
}

inline vec3 normalize( const vec3& v )
{
    return v / length( v );
}

template <typename Generator>
vec3 random_vec3( Generator&& gen )
{
    std::uniform_real_distribution<float> distribution;
    return { distribution( gen ), distribution( gen ), distribution( gen ) };
}

template <typename Generator>
vec3 random_vec3( Generator&& gen, float a, float b )
{
    std::uniform_real_distribution<float> distribution( a, b );
    return { distribution( gen ), distribution( gen ), distribution( gen ) };
}

template <typename Generator>
vec3 random_vec3_in_unit_sphere( Generator&& gen )
{
    vec3 p;
    do
    {
        p = random_vec3( gen, -1.f, +1.f );
    } while ( length_squared( p ) >= 1.f );
    return p;
}

template <typename Generator>
vec3 random_vec3_unit_vector( Generator&& gen )
{
    return normalize( random_vec3_in_unit_sphere( gen ) );
}

template <typename Generator>
vec3 random_vec3_in_hemisphere( Generator&& gen, const vec3& normal )
{
    auto in_unit_sphere = random_vec3_in_unit_sphere( gen );
    if ( dot( in_unit_sphere, normal ) > 0.f )
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline std::ostream& operator<<( std::ostream& os, const vec3& v )
{
    return os << v.x() << ' ' << v.y() << ' ' << v.z();
}
}  // namespace rtow
