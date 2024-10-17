#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    while (!game.isQuitting) {

        game.handleEvents();
        game.update();
        game.render();
    }

    game.dispose();
    return 0;
}
