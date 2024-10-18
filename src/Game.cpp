#include "Game.h"
#include "LocalPlayerCharacter.h"
#include "TileMap.h"
#include "Math.h"
#include "InputEvent.h"

SDL_Texture* spriteTexture;
std::vector<SceneObject*> sceneObjects;
LocalPlayerCharacter* localPlayerCharacter;
Label* label = nullptr;
Label* lbl_screen_clicked = nullptr;
Label* lbl_world_clicked = nullptr;
Label* lbl_cell_clicked = nullptr;

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

    TileMap* tileMap = new TileMap();
    sceneObjects.push_back(tileMap);
    for(int y = 0; y < 8; y++)
    for(int x = 0; x < 8; x++)
        tileMap->SetTile(x, y, 0);

    localPlayerCharacter = new LocalPlayerCharacter("res/sprite.png", Vector2i(50, 50));
    sceneObjects.push_back(localPlayerCharacter);

    SDL_Color WHITE = { 255, 255, 255, 255 };
    label = new Label("FRAMERATE: {0}", "res/PIXEARG_.TTF", 12, WHITE);
    sceneObjects.push_back(label);

    lbl_screen_clicked = new Label("CLICKED: {0}", "res/PIXEARG_.TTF", 12, WHITE);
    lbl_screen_clicked->transform.Translate(Vector2i::DOWN * 18);
    sceneObjects.push_back(lbl_screen_clicked); 

    lbl_world_clicked = new Label("CLICKED: {0}", "res/PIXEARG_.TTF", 12, WHITE);
    lbl_world_clicked->transform.Translate(Vector2i::DOWN * 36);
    sceneObjects.push_back(lbl_world_clicked); 

    lbl_cell_clicked = new Label("CLICKED: {0}", "res/PIXEARG_.TTF", 12, WHITE);
    lbl_cell_clicked->transform.Translate(Vector2i::DOWN * 54);
    sceneObjects.push_back(lbl_cell_clicked);        
    
    return true;
}


void Game::update() {
    label->setText("Framerate: " + std::to_string(fps));
    for (auto& obj : sceneObjects) {
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
        if (e.type == SDL_KEYDOWN)
        {
            const Uint8* state = SDL_GetKeyboardState(NULL);
            Vector2i inputVector(
                state[SDL_SCANCODE_A] ? -1 : state[SDL_SCANCODE_D] ? 1 : 0,
                state[SDL_SCANCODE_S] ? 1 : state[SDL_SCANCODE_W] ? -1 : 0 
            );
            Vector2 dir = Math::ToIsometric(inputVector);
            localPlayerCharacter->transform.Translate(dir);
            lbl_screen_clicked->setText(dir.ToString());

        }
        if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
            InputEvent ievent(e);
            lbl_screen_clicked->setText("clicked (screen): " + ievent.screen.ToString());
            lbl_world_clicked->setText("clicked (world): " + ievent.world.ToString());
            lbl_cell_clicked->setText("clicked (cell): " + ievent.cell.ToString());
            for (auto& obj : sceneObjects) {
                obj->HandleInput(ievent);
            }
        }
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
    }
}