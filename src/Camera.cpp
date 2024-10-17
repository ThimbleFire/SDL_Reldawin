#include "Camera.h"

Camera camera;

SDL_Rect Camera::getCameraRect() const {
    return {position.x, position.y, width, height};
}
