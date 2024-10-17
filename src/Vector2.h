#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "Base.h"

class Vector2 : public Base {
public:
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
    ~Vector2() {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(int scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    bool operator<(const Vector2& other) const {
        if (x < other.x) return true;
        if (x == other.x && y < other.y) return true;
        return false;
    }

    std::string ToString() const override {
        return std::to_string(x) + ", " + std::to_string(y);
    }

    // parameter: unsigned char buffer[sizeof(float) * 2];
    // void ToByteArray(unsigned char* buffer) const {
    //     std::memcpy(buffer, &x, sizeof(x));       // Copy x to the buffer
    //     std::memcpy(buffer + sizeof(x), &y, sizeof(y)); // Copy y to the buffer
    // }

    // Directional constants
    static const Vector2 UP;
    static const Vector2 DOWN;
    static const Vector2 LEFT;
    static const Vector2 RIGHT;
    static const Vector2 ZERO;
    static const Vector2 ONE;

    // Data members
    float x = 0;
    float y = 0;
};

#endif
