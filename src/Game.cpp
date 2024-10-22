#include "Game.h"
#include "TestWindow.h"
#include "Engine/TileMaster.h"
#include "LocalPlayerCharacter.h"

#include "Engine/UI.h"

Game::Game() {
}

Game::~Game() {

}

bool Game::init() {
    if (!Engine::init()) {
        return false;
    }

    TileMaster* tileMaster = new TileMaster();
    sceneObjects.push_back(tileMaster);

    LocalPlayerCharacter* localPlayerCharacter = new LocalPlayerCharacter("res/sprite.png", Vector2i(24, 24), tileMaster);
    sceneObjects.push_back(localPlayerCharacter);  

    TestWindow* testWindow = new TestWindow();
    sceneObjects.push_back(testWindow);  

    camera.setPosition(localPlayerCharacter->transform.position);

    localPlayerCharacter->transform.onPositionChanged.subscribe([this, localPlayerCharacter](){
        camera.setPosition(localPlayerCharacter->transform.position);
    });
    return true;
}