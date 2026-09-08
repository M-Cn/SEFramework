#ifndef VECTOR_INL
#define VECTOR_INL

#include <cmath>

namespace rlib
{
    struct Vector2
    {
        Vector2() : X(0.f), Y(0.f) {}
        Vector2(float _x, float _y) : X(_x), Y(_y) {}
        Vector2(const Vector2& other) { X = other.X; Y = other.Y; }

        Vector2 operator+(const Vector2& other) const { return Vector2(X + other.X, Y + other.Y); }
        Vector2 operator-(const Vector2& other) const { return Vector2(X - other.X, Y - other.Y); }
        Vector2 operator*(float scalar) const { return Vector2(X * scalar, Y * scalar); }

        Vector2& operator+=(const Vector2& other) 
        { 
            X += other.X; 
            Y += other.Y; 
            return *this; 
        }

        Vector2& operator-=(const Vector2& other) 
        { 
            X -= other.X; 
            Y -= other.Y; 
            return *this; 
        }

        Vector2& operator*=(float scalar) 
        { 
            X *= scalar; 
            Y *= scalar; 
            return *this; 
        }

        float dot(const Vector2& other) const { return X * other.X + Y * other.Y; }
        Vector2 cross(const Vector2& other) const { return Vector2(Y * other.X - X * other.Y, X * other.Y - Y * other.X); }

        float length() const { return sqrtf(lengthSq()); }
        float lengthSq() const { return X * X + Y * Y; }

        float distanceTo(const Vector2& other) const { return (other - *this).length(); }

        Vector2 normalized() const 
        { 
            float len = length();
            
            if (len == 0.f) return Vector2(0.f, 0.f);

            return Vector2(X / len, Y / len); 
        }

        union
        {
            float V[2];
            struct
            {
                float X;
                float Y;
            };
        };
    };

    struct Vector3
    {
        Vector3() : X(0.f), Y(0.f), Z(0.f) {}
        Vector3(float _x, float _y, float _z) : X(_x), Y(_y), Z(_z) {}
        Vector3(const Vector3& other) { X = other.X; Y = other.Y; Z = other.Z; }

        Vector3 operator+(const Vector3& other) const { return Vector3(X + other.X, Y + other.Y, Z + other.Z); }
        Vector3 operator-(const Vector3& other) const { return Vector3(X - other.X, Y - other.Y, Z - other.Z); }
        Vector3 operator*(float scalar) const { return Vector3(X * scalar, Y * scalar, Z * scalar); }

        Vector3& operator+=(const Vector3& other) 
        { 
            X += other.X; 
            Y += other.Y; 
            Z += other.Z; 
            return *this; 
        }

        Vector3& operator-=(const Vector3& other) 
        { 
            X -= other.X; 
            Y -= other.Y; 
            Z -= other.Z; 
            return *this; 
        }

        Vector3& operator*=(float scalar) 
        { 
            X *= scalar; 
            Y *= scalar; 
            Z *= scalar; 
            return *this; 
        }

        float dot(const Vector3& other) const { return X * other.X + Y * other.Y + Z * other.Z; }
        Vector3 cross(const Vector3& other) const { return Vector3(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X); }

        float length() const { return sqrtf(lengthSq()); }
        float lengthSq() const { return X * X + Y * Y + Z * Z; }

        float distanceTo(const Vector3& other) const { return (other - *this).length(); }

        Vector3 normalized() const 
        { 
            float len = length();
            
            if (len == 0.f) return Vector3(0.f, 0.f, 0.f);

            return Vector3(X / len, Y / len, Z / len); 
        }

        union
        {
            float V[3];
            struct
            {
                float X;
                float Y;
                float Z;
            };
        };
    };

    static Vector2 VECTOR2_ZERO = Vector2(0.f, 0.f);
    static Vector2 VECTOR2_UNITX = Vector2(1.f, 0.f);
    static Vector2 VECTOR2_UNITY = Vector2(0.f, 1.f);

    static Vector3 VECTOR3_ZERO = Vector3(0.f, 0.f, 0.f);
    static Vector3 VECTOR3_UNITX = Vector3(1.f, 0.f, 0.f);
    static Vector3 VECTOR3_UNITY = Vector3(0.f, 1.f, 0.f);
    static Vector3 VECTOR3_UNITZ = Vector3(0.f, 0.f, 1.f);
}

#endif // VECTOR_INL