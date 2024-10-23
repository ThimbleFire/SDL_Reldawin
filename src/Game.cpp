#include "Engine/TileMaster.h"
#include "Engine/UI.h"

#include "Game.h"
#include "TestWindow.h"
#include "LocalPlayerCharacter.h"

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
    
    TestWindow* testWindow = new TestWindow();
    sceneObjects.push_back(testWindow);  
    
    UILabel* lbl_framerate = dynamic_cast<UILabel*>(testWindow->get_child(4));
    UILabel* lbl_LPCPosition = dynamic_cast<UILabel*>(testWindow->get_child(5));
    UILabel* lbl_LPCCell = dynamic_cast<UILabel*>(testWindow->get_child(6));
    UILabel* lbl_cursor_over_cell = dynamic_cast<UILabel*>(testWindow->get_child(7));

    LocalPlayerCharacter* localPlayerCharacter = new LocalPlayerCharacter("res/sprite.png", Vector2i(24, 24), tileMaster);
    sceneObjects.push_back(localPlayerCharacter);  

    camera.setPosition(localPlayerCharacter->transform.position);

    localPlayerCharacter->transform.onPositionChanged.subscribe([this, localPlayerCharacter](){
        camera.setPosition(localPlayerCharacter->transform.position);
        lbl_LPCPosition->setText(localPlayerCharacter->transform.position);
        lbl_LPCCell->setText(Math::WorldToCell(localPlayerCharacter->transform.position));
    });
    
    
    return true;
}
