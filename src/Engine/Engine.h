#ifndef Engine_H
#define Engine_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "SceneObject.h"

class Engine {
public:
    Engine();
    ~Engine();
    
    virtual bool init();

    void handleEvents();
    void render();
    void update();

    //temporary window
    void UpdateDebugger(int fps);

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

#endif // Engine_H
