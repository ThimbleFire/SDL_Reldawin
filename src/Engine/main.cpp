#include "../Game.h"

Uint32 lastTime = 0, currentTime;
float deltaTime = 0.0f;

int main(int argc, char* argv[]) {
    Game game;

    void calculateDeltaTime();

    if (!game.init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    while (!game.isQuitting) {

        calculateDeltaTime();

        game.handleEvents();
        game.update(deltaTime);
        game.render();
    }
    
    return 0;
}

void calculateDeltaTime() {
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
    lastTime = currentTime;
}
