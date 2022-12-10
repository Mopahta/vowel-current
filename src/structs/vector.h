#include "..\imports.h"

#ifndef _VECTOR3D
#define _VECTOR3D

struct Vector3 {
    float x, y, z;
    constexpr Vector3 (float x = 0.f, float y = 0.f, float z = 0.f) :
        x(x), y(y), z(z) {}

    constexpr const Vector3 operator-(const Vector3& other) const noexcept {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    constexpr const Vector3 operator+(const Vector3& other) const noexcept {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    constexpr const Vector3 operator/(const float num) const noexcept {
        return Vector3(x / num, y / num, z / num);
    }

    constexpr const Vector3 operator*(const float num) const noexcept {
        return Vector3(x * num, y * num, z * num);
    }

    constexpr const Vector3 toAngle() const noexcept {
        return Vector3 {
            std::atan2(-z , std::hypot(x, y)) * (180.0f / M_PI),
            std::atan2(y, x) * (180.0f / M_PI),
            0.0f
        };
    }

    constexpr const bool notChanged() {
        return x == 0.f && y == 0.f && z == 0.f;
    }

};


#endif