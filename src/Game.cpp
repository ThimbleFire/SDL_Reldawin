#include "Game.h"
#include "LocalPlayerCharacter.h"
#include "TileMap.h"
#include "Math.h"
#include "UI.h"
#include "TestWindow.h"

SDL_Texture* spriteTexture = nullptr;
LocalPlayerCharacter* localPlayerCharacter = nullptr;
UILabel* lbl_framerate = nullptr;
UILabel* lbl_LPCPosition = nullptr;

std::map<Vector2i, TileMap*> stuff;

Game::Game() {
    
}

Game::~Game() {
    dispose();
}

bool Game::init() {
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

    CreateStartChunks(1, 1);

    localPlayerCharacter = new LocalPlayerCharacter("res/sprite.png", Vector2i(50, 50));
    sceneObjects.push_back(localPlayerCharacter);
    
    TestWindow* testWindow = new TestWindow();
    sceneObjects.push_back(testWindow);

    // debugging
    lbl_framerate = dynamic_cast<UILabel*>(testWindow->get_child(4));
    lbl_LPCPosition = dynamic_cast<UILabel*>(testWindow->get_child(5));

    return true;
}

void Game::CreateChunk(int w, int h) {
    TileMap* tileMap = new TileMap();
    for(int y = h * 16; y < (h + 1) * 16; y++)
    for(int x = w * 16; x < (w + 1) * 16; x++)
        tileMap->SetTile(x, y, 0);

    stuff[Vector2i(w, h)] = tileMap;
}

void Game::CreateStartChunks(int w, int h) {
    for(int x = w - 1; x < w + 2; x++) 
    for(int y = h - 1; y < h + 2; y++) {
        CreateChunk(x, y);
    }
}

void Game::update() {
    for (auto& obj : sceneObjects) {
        //if(!obj->visible) continue;
        obj->Update();
    }
    camera.setPosition(localPlayerCharacter->transform.position);
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {

        if (e.type == SDL_QUIT) {
            printf("Exiting game...\n");
            isQuitting = true;
        }

        InputEvent ievent(e);
        for (auto& obj : sceneObjects) {
            //if(!obj->visible) continue;
            obj->HandleInput(ievent);
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for(const auto& pair : stuff) {
        pair.second->Draw();
    }

    for (auto& obj : sceneObjects) {
        //if(!obj->visible) continue;
        obj->Draw();
    }
    
    SDL_RenderPresent(renderer);

    calculateFramerate();
}

void Game::dispose() {
    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for (auto& obj : sceneObjects) {
        obj->dispose();
        obj = nullptr;
    }
    sceneObjects.clear();
    g_resourceRepository.dispose();
    IMG_Quit();
    SDL_Quit();
}

void Game::calculateFramerate() {
    // Update frame count
    frameCount++;

    // Calculate FPS
    currentTime = SDL_GetTicks(); // Get the current time in milliseconds
    if (currentTime - lastTime >= 1000) { // If 1 second has passed
        fps = frameCount; // Set FPS to frame count in that second
        frameCount = 0; // Reset frame count
        lastTime = currentTime; // Reset lastTime
            
        UpdateDebugger(fps);
    }
}

void Game::UpdateDebugger(int fps) {
    lbl_framerate->SetText("FPS: " + std::to_string(fps));    
    lbl_LPCPosition->SetText("Position: " + localPlayerCharacter->transform.position.ToString());
}