#ifndef _VECTOR2I_H_
#define _VECTOR2I_H_

#include "Base.h"
#include "Vector2.h"
#include <cmath>  // For sqrt

class Vector2i : public Base {
public:
    Vector2i() : x(0), y(0) {}
    Vector2i(int x, int y) : x(x), y(y) {}
    ~Vector2i() {}

    Vector2i operator+(const Vector2i& other) const {
        return Vector2i(x + other.x, y + other.y);
    }

    Vector2i operator+(const Vector2& other) const {
        return Vector2i(x + other.x, y + other.y);
    }

    Vector2i operator-(const Vector2i& other) const {
        return Vector2i(x - other.x, y - other.y);
    }
    
    Vector2i operator-(const Vector2& other) const {
        return Vector2i(x - static_cast<int>(other.x), y - static_cast<int>(other.y));
    }

    Vector2i operator*(int scalar) const {
        return Vector2i(x * scalar, y * scalar);
    }   

    Vector2 ToVec2() const {
        return Vector2(static_cast<float>(x), static_cast<float>(y));
    }

    std::string ToString() const override {
        return std::to_string(x) + ", " + std::to_string(y);
    }

    bool operator<(const Vector2i& other) const {
        if (x < other.x) return true;
        if (x == other.x && y < other.y) return true;
        return false;
    }
    
    Vector2i operator/(int scalar) const {
        if (scalar != 0) {
            return Vector2i(x / scalar, y / scalar);
        }
        // Handle division by zero as needed, e.g., throw an exception or return zero vector
        return Vector2i(0, 0); // This can be modified to suit your error handling preference
    }

    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void set(Vector2i value) {
        this->x = value.x;
        this->y = value.y;
    }

    float distance_to(const Vector2i& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Vector2 normalized() const {
        float magnitude = std::sqrt(x * x + y * y);
        if (magnitude == 0.0f) {
            return Vector2(0.0f, 0.0f);
        }
        return Vector2(static_cast<float>(x) / magnitude, static_cast<float>(y) / magnitude);
    }

    // Directional constants
    static const Vector2i UP;
    static const Vector2i DOWN;
    static const Vector2i LEFT;
    static const Vector2i RIGHT;
    static const Vector2i ZERO;
    static const Vector2i ONE;

    // Data members
    int x = 0;
    int y = 0;
};

#endif