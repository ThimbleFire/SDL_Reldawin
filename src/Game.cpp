#include "Game.h"
#include "LocalPlayerCharacter.h"
#include "TileMap.h"

SDL_Texture* spriteTexture;
std::vector<SceneObject*> sceneObjects;
Label* label = nullptr;

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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
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
    LocalPlayerCharacter* localPlayerCharacter = new LocalPlayerCharacter("res/sprite.png", Vector2i::ZERO);
    sceneObjects.push_back(localPlayerCharacter);

    SDL_Color WHITE = { 255, 255, 255, 255 };
    label = new Label("FRAMERATE: {0}", "res/PIXEARG_.TTF", 12, WHITE);
    sceneObjects.push_back(label);

    TileMap* tileMap = new TileMap();
    sceneObjects.push_back(tileMap);
    for(int y = 0; y < 8; y++)
    for(int x = 0; x < 8; x++)
        tileMap->SetTile(x, y, 0);
    
    return true;
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
    }
}

void Game::update() {
    label->setText("Framerate: " + std::to_string(fps));
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            // Handle quit event
            printf("Exiting game...\n");
            isQuitting = true;
        }

        // Check for arrow key presses
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    camera.Translate(Vector2i::UP * 5);
                    label->setText(camera.ToString());
                    break;
                case SDLK_DOWN:
                    camera.Translate(Vector2i::DOWN * 5);
                    label->setText(camera.ToString());
                    break;
                case SDLK_LEFT:
                    camera.Translate(Vector2i::LEFT * 5);
                    label->setText(camera.ToString());
                    break;
                case SDLK_RIGHT:
                    camera.Translate(Vector2i::RIGHT * 5);
                    label->setText(camera.ToString());
                    break;
            }
        }
    }

    for (auto& obj : sceneObjects) {
        obj->Update();
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (auto& obj : sceneObjects) {
        obj->Draw();
    }
    
    SDL_RenderPresent(renderer);

    calculateFramerate();
}

void Game::dispose() {
    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    g_resourceRepository.dispose();
    IMG_Quit();
    SDL_Quit();
}
