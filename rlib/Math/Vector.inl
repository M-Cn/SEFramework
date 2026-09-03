#ifndef VECTOR3_INL
#define VECTOR3_INL

#include <cmath>

class Vector3
{
public:
    Vector3() : m_X(0.f), m_Y(0.f), m_Z(0.f) {}
    Vector3(float _x, float _y, float _z) : m_X(_x), m_Y(_y), m_Z(_z) {}
    Vector3(const Vector3& other) { m_X = other.m_X; m_Y = other.m_Y; m_Z = other.m_Z; }

    float X() const { return m_X; }
    float Y() const { return m_Y; }
    float Z() const { return m_Z; }

    Vector3 operator+(const Vector3& other) const { return Vector3(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z); }
    Vector3 operator-(const Vector3& other) const { return Vector3(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z); }
    Vector3 operator*(float scalar) const { return Vector3(m_X * scalar, m_Y * scalar, m_Z * scalar); }

    float dot(const Vector3& other) const { return m_X * other.m_X + m_Y * other.m_Y + m_Z * other.m_Z; }
    Vector3 cross(const Vector3& other) const { return Vector3(m_Y * other.m_Z - m_Z * other.m_Y, m_Z * other.m_X - m_X * other.m_Z, m_X * other.m_Y - m_Y * other.m_X); }

    float length() const { return sqrtf(lengthSq()); }
    float lengthSq() const { return m_X * m_X + m_Y * m_Y + m_Z * m_Z; }

    float distanceTo(const Vector3& other) const { return (other - *this).length(); }

    Vector3 normalized() const 
    { 
        float len = length();
        
        if (len == 0.f) return Vector3(0.f, 0.f, 0.f);

        return Vector3(m_X / len, m_Y / len, m_Z / len); 
    }
private:
    float m_X;
    float m_Y;
    float m_Z;
};

static Vector3 VECTOR3_ZERO = Vector3(0.f, 0.f, 0.f);

#endif