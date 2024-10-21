#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL2/SDL.h>
#include "Transform.h"

class Camera : public Transform {
public:
    Camera() {}
    void setSize(float width, float height) {
        size.set(width, height);
    }
    Vector2 ScreenToWorld(int x, int y) {
        return Vector2(x + position.x, y + position.y);
    }
    void setPosition(Vector2 position) {
        this->position = position - size / 2;
    }
};

extern Camera camera;

#endif
