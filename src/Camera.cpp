#include "Camera.h"

Camera::Camera(int width, int height) : width(width), height(height) {
    this->width = width;
    this->height = height;
}

SDL_Rect Camera::getCameraRect() const {
    return {position.x, position.y, width, height};
}
