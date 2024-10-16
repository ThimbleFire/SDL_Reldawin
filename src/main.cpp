#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();
    void close();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* spriteTexture;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Texture* loadTexture(const char* path);
};

Game::Game() : window(nullptr), renderer(nullptr), spriteTexture(nullptr) {}

Game::~Game() {
    close();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Sprite Rendering",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    return true;
}

SDL_Texture* Game::loadTexture(const char* path) {
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) {
        std::cerr << "Unable to load image " << path << "! IMG_Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!newTexture) {
        std::cerr << "Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void Game::close() {
    if (spriteTexture) {
        SDL_DestroyTexture(spriteTexture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }

    IMG_Quit();
    SDL_Quit();
}

void Game::run() {
    spriteTexture = loadTexture("res/sprite.png");
    if (!spriteTexture) {
        std::cerr << "Failed to load texture!" << std::endl;
        close();
        return;
    }

    SDL_Event e;
    bool quit = false;

    int spriteWidth, spriteHeight;
    SDL_QueryTexture(spriteTexture, nullptr, nullptr, &spriteWidth, &spriteHeight);
    SDL_Rect destRect = { (SCREEN_WIDTH - spriteWidth) / 2, (SCREEN_HEIGHT - spriteHeight) / 2, spriteWidth, spriteHeight };

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, spriteTexture, nullptr, &destRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }
}

int main(int argc, char* argv[]) {
    Game game;
    if (!game.init()) {
        return 1;
    }
    game.run();
    return 0;
}
