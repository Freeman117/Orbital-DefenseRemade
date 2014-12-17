#pragma once
#ifndef VECTOR2_PMATH_H
#define VECTOR2_PMATH_H

#include <iostream>
#include <string>

namespace pmath
{
    template<typename T>
    class Vector2
    {
    public:
        Vector2();
        Vector2(const T& x, const T& y);
        explicit Vector2(const T& value);
        Vector2(const Vector2& vector);
        template<typename T2>
        Vector2(const Vector2<T2>& vector);
        ~Vector2();

        // Scales(multiplies) respective component with scaleVector component
        Vector2& scale(const Vector2& scaleVector);
        // Scales(multiplies) respective component with given component
        Vector2& scale(const T& x, const T& y);
        // Scales the whole vector with the number
        Vector2& scale(const T& scale);

        // Get the angle between the x axis and the vector
        T angle() const;

        T dot(const Vector2& other) const;
        static T dot(const Vector2& vec1, const Vector2& vec2);

        // Convenience function for returning the Z value of
        // the cross product of two (x,y,0) vectors
        T cross(const Vector2& other) const;
        static T cross(const Vector2& vec1, const Vector2& vec2);

        double lengthSquared() const;
        double length() const;

        static double distance(const Vector2& vec1, const Vector2& vec2);

        // Normalizes the vector and returns the normalized vector
        Vector2& normalize();
        // Returns the normalized vector. doesn't modify original
        Vector2 normalized() const;

        // Deprecated. use normalized()
        Vector2 unitVector() const;

        // Check if the vector is normalized
        bool isNormalized() const;

        // Deprecated. use isNormalized()
        bool isUnitVector() const;

        static Vector2 lerp(const Vector2& vec1, const Vector2& vec2, const T& t);

        std::string toString() const;

        #pragma region Operators
        // Comparison
        bool operator ==(const Vector2& right) const;
        bool operator !=(const Vector2& right) const;
        bool operator  >(const Vector2& right) const;
        bool operator  <(const Vector2& right) const;
        bool operator >=(const Vector2& right) const;
        bool operator <=(const Vector2& right) const;

        // Assignment
        Vector2& operator  =(const Vector2& right);
        Vector2& operator +=(const Vector2& right);
        Vector2& operator -=(const Vector2& right);
        Vector2& operator *=(const T& right);
        Vector2& operator /=(const T& right);

        // Arithmetic
        Vector2 operator +(const Vector2<T>& right) const;
        Vector2 operator -() const;
        Vector2 operator -(const Vector2<T>& right) const;
        Vector2 operator *(const T& right) const;
        Vector2 operator /(const T& right) const;

        // Member access
        T& operator [](const unsigned int index);
        const T& operator [](const unsigned int index) const;
        #pragma endregion

        union{ T x, w; };
        union{ T y, h; };

        static const unsigned int COMPONENTS = 2;
    };

    template<typename T>
    Vector2<T> operator*(const T& left, const Vector2<T>& right);

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vector2<T>& right);

    typedef Vector2<float>          Vec2;
    typedef Vector2<float>          Vec2f;
    typedef Vector2<double>         Vec2d;
    typedef Vector2<int>            Vec2i;
    typedef Vector2<unsigned int>   Vec2u;
}

#include "inl/Vector2.inl"
#endif