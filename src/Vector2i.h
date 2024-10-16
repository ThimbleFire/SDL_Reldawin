#ifndef _VECTOR2I_H_
#define _VECTOR2I_H_

#include "Base.h"

class Vector2i : public Base {
public:
    Vector2i() : x(0), y(0) {}
    Vector2i(int x, int y) : x(x), y(y) {}
    ~Vector2i() {}

    Vector2i operator+(const Vector2i& other) const {
        return Vector2i(x + other.x, y + other.y);
    }

    Vector2i operator-(const Vector2i& other) const {
        return Vector2i(x - other.x, y - other.y);
    }

    Vector2i operator*(int scalar) const {
        return Vector2i(x * scalar, y * scalar);
    }

    std::string ToString() const override {
        return std::to_string(x) + ", " + std::to_string(y);
    }

    // parameter: unsigned char buffer[sizeof(int) * 2];
    void ToByteArray(unsigned char* buffer) const {
        std::memcpy(buffer, &x, sizeof(x));       // Copy x to the buffer
        std::memcpy(buffer + sizeof(x), &y, sizeof(y)); // Copy y to the buffer
    }

    // Directional constants
    static const Vector2i UP;
    static const Vector2i DOWN;
    static const Vector2i LEFT;
    static const Vector2i RIGHT;

    // Data members
    int x = 0;
    int y = 0;
};

#endif
