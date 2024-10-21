#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL2/SDL.h>
#include "Transform.h"

class Camera : public Transform {
public:
    Camera() {}
    SDL_Rect getCameraRect() const;
    void setSize(int width, int height) {
        this->width = width;
        this->height = height;
    }
    Vector2 ScreenToWorld(int x, int y) {
        return Vector2(x + position.x, y + position.y);
    }
    void setPosition(Vector2 position) {
        this->position = position - Vector2(width / 2, height / 2);
    }

private:
    int width;       // Width of the camera viewport
    int height;      // Height of the camera viewport
};

extern Camera camera;

#endif
