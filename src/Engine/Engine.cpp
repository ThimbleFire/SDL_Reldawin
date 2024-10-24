#include "Engine.h"
#include "Math.h"
#include "UI.h"
#include "TileMaster.h"

Engine::Engine() {
    
}

Engine::~Engine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for (auto& obj : sceneObjects) {
        delete obj;
        obj = nullptr;
    }
    sceneObjects.clear();
    IMG_Quit();
    SDL_Quit();
}

bool Engine::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDL Sprite Rendering",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    g_resourceRepository.Initialize(renderer);
    

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", SDL_GetError());
        return false;
    }
 
    camera.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    return true;
}

void Engine::update(float delta) {
    for (auto& obj : sceneObjects) {
        //if(!obj->visible) continue;
        obj->Update(delta);
    }
}

void Engine::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {

        if (e.type == SDL_QUIT) {
            printf("Exiting Engine...\n");
            isQuitting = true;
        }

        InputEvent ievent(e);
        for (auto& obj : sceneObjects) {
            if(ievent.handled)
                return;
            if(!obj->visible) 
                continue;
            obj->HandleInput(ievent);
        }
    }
}

void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (auto& obj : sceneObjects) {
        //if(!obj->visible) continue;
        obj->Draw();
    }
    
    SDL_RenderPresent(renderer);

    calculateFramerate();
}

void Engine::calculateFramerate() {
    // Update frame count
    frameCount++;

    // Calculate FPS
    currentTime = SDL_GetTicks(); // Get the current time in milliseconds
    if (currentTime - lastTime >= 1000) { // If 1 second has passed
        fps = frameCount; // Set FPS to frame count in that second
        frameCount = 0; // Reset frame count
        lastTime = currentTime; // Reset lastTime
    }
}