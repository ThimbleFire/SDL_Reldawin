#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "SceneObject.h"

class Game {
public:
    Game();
    ~Game();
    
    bool init();

    void handleEvents();
    void render();
    void update();

    //temporary window
    void UpdateDebugger(int fps);

    void CreateChunk(int x, int y);
    void CreateStartChunks(int x, int y);

public:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    bool isQuitting = false;

protected:
    std::vector<SceneObject*> sceneObjects;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* spriteTexture;

    Uint32 lastTime; // Last frame time
    Uint32 currentTime; // Current frame time
    int frameCount; // Count frames
    float fps; // Store FPS

    void calculateFramerate();
};

#endif // GAME_H
