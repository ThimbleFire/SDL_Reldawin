#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "Base.h"
#include <cmath>  // For sqrt
#include <sstream>
#include <iomanip> // For std::setprecision

class Vector2 : public Base {
public:
    // Constructors
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}
    ~Vector2() {}

    // Operator overloads for Vector2
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const {
        if (scalar != 0.0f) {
            return Vector2(x / scalar, y / scalar);
        }
        // Handle division by zero
        return Vector2(0.0f, 0.0f);  // This can be modified to suit your error handling preference
    }

    // Comparison operator
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    // Conversion to string for debugging purposes
    std::string ToString() const override {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << x << ", " << y;
        return ss.str();
    }

    // Less-than operator (for sorting or comparisons)
    bool operator<(const Vector2& other) const {
        if (x < other.x) return true;
        if (x == other.x && y < other.y) return true;
        return false;
    }

    // Setters
    void set(float x, float y) {
        this->x = x;
        this->y = y;
    }

    void set(const Vector2& value) {
        this->x = value.x;
        this->y = value.y;
    }

    // Distance calculation between two vectors
    float distance_to(const Vector2& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Normalization
    Vector2 normalized() const {
        float magnitude = std::sqrt(x * x + y * y);
        if (magnitude == 0.0f) {
            return Vector2(0.0f, 0.0f);
        }
        return Vector2(x / magnitude, y / magnitude);
    }

    // Directional constants
    static const Vector2 UP;
    static const Vector2 DOWN;
    static const Vector2 LEFT;
    static const Vector2 RIGHT;
    static const Vector2 ZERO;
    static const Vector2 ONE;

    // Data members
    float x = 0.0f;
    float y = 0.0f;
};

#endif
