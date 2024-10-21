#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include <SDL2/SDL_rect.h>
#include <map>
#include "SceneObject.h"
#include "Camera.h"
#include "ResourceRepository.h"

class TileMap : public SceneObject {

    public:
        enum TileType {
            VOID
        };

    public:
        TileMap();
        ~TileMap();  
        void SetTile(int x, int y, int8_t id);        
        void Draw() const override;
        void HandleInput(InputEvent& event) override;
    private:
        std::map<Vector2i, SDL_Rect> tiles;

};

#endif