#include "Engine/TileMaster.h"
#include "Engine/UI.h"

#include "Game.h"
#include "TestWindow.h"
#include "LocalPlayerCharacter.h"
#include "Engine/Cursor.h"

UILabel* lbl_framerate;
UILabel* lbl_LPCPosition;
UILabel* lbl_LPCCell;
UILabel* lbl_cursor_over_cell;
Cursor* cursor;

Game::Game() {
}

Game::~Game() {

}

bool Game::init() {
    if (!Engine::init()) {
        return false;
    }

    TileMaster* tileMaster = new TileMaster("res/tile.png");
    sceneObjects.push_back(tileMaster);
    
    TestWindow* testWindow = new TestWindow();
    sceneObjects.push_back(testWindow);  
    
    lbl_framerate = dynamic_cast<UILabel*>(testWindow->get_child(4));
    lbl_LPCPosition = dynamic_cast<UILabel*>(testWindow->get_child(5));
    lbl_LPCCell = dynamic_cast<UILabel*>(testWindow->get_child(6));
    lbl_cursor_over_cell = dynamic_cast<UILabel*>(testWindow->get_child(7));

    LocalPlayerCharacter* localPlayerCharacter = new LocalPlayerCharacter("res/sprite.png", Vector2i(24, 24), tileMaster);
    sceneObjects.push_back(localPlayerCharacter);  

    camera.setPosition(localPlayerCharacter->transform.position);

    localPlayerCharacter->transform.onPositionChanged.subscribe([this, localPlayerCharacter](){
        camera.setPosition(localPlayerCharacter->transform.position);
        lbl_LPCPosition->SetText(localPlayerCharacter->transform.position.ToString());
        lbl_LPCCell->SetText(Math::WorldToCell(localPlayerCharacter->transform.position).ToString());
    });

    cursor = new Cursor("res/cursor.png");
    sceneObjects.push_back(cursor);   
    
    return true;
}
