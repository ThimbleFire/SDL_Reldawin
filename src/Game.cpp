#include "Game.h"
#include "LocalPlayerCharacter.h"
#include "Math.h"
#include "UI.h"
#include "TestWindow.h"
#include "TileMaster.h"

SDL_Texture* spriteTexture = nullptr;
LocalPlayerCharacter* localPlayerCharacter = nullptr;
UILabel* lbl_framerate = nullptr;
UILabel* lbl_LPCPosition = nullptr;
UILabel* lbl_LPCCell = nullptr;

Game::Game() {
    
}

Game::~Game() {
    SDL_DestroyTexture(spriteTexture);
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

    TileMaster* tileMaster = new TileMaster();
    sceneObjects.push_back(tileMaster);

    localPlayerCharacter = new LocalPlayerCharacter("res/sprite.png", Vector2i(0, 0), tileMaster);
    sceneObjects.push_back(localPlayerCharacter);

    localPlayerCharacter->transform.onPositionChanged.subscribe([this](){
        lbl_LPCPosition->SetText("Position: " + localPlayerCharacter->transform.position.ToString());
        lbl_LPCCell->SetText("Cell: " + localPlayerCharacter->cell_global().ToString());
    });
    
    TestWindow* testWindow = new TestWindow();
    sceneObjects.push_back(testWindow);

    // debugging
    lbl_framerate = dynamic_cast<UILabel*>(testWindow->get_child(4));
    lbl_LPCPosition = dynamic_cast<UILabel*>(testWindow->get_child(5));
    lbl_LPCCell = dynamic_cast<UILabel*>(testWindow->get_child(6));

    return true;
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

    for (auto& obj : sceneObjects) {
        //if(!obj->visible) continue;
        obj->Draw();
    }
    
    SDL_RenderPresent(renderer);

    calculateFramerate();
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
}