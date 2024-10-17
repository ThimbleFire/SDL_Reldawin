#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Base.h"
#include "Vector2i.h"
#include "Vector2.h"

class Transform : public Base {
    public:
        void Translate(int x, int y);
        void Translate(Vector2i position);
        void Translate(Vector2 position);
        std::string ToString() const override {
            return std::to_string(position.x) + ", " + std::to_string(position.y);
        }
    public:
        Vector2i position;
};

#endif