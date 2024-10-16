#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Camera.h"
#include "ResourceRepository.h"
#include "Label.h"

class Game {
public:
    Game();
    ~Game();
    
    bool init();
    void dispose();

    void handleEvents();
    void render();
    void update();

    bool isQuitting = false;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* spriteTexture;
    Camera* camera;


    Uint32 lastTime; // Last frame time
    Uint32 currentTime; // Current frame time
    int frameCount; // Count frames
    float fps; // Store FPS

    void calculateFramerate();
};

#endif // GAME_H
