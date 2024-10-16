#include <SDL2/SDL.h>
#include "Transform.h"

class Camera : public Transform {
public:
    Camera(int width, int height);
    SDL_Rect getCameraRect() const;

private:
    int width;       // Width of the camera viewport
    int height;      // Height of the camera viewport
};