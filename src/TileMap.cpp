#include "TileMap.h"
#include "Math.h"

SDL_Texture* tile_texture;

TileMap::TileMap() {
    tile_texture = g_resourceRepository.load("res/tile.png");
}

TileMap::~TileMap() {
    g_resourceRepository.unload("res/tile.png");
}

void TileMap::SetTile(int x, int y, int8_t id) {    
    tiles[Vector2i(x, y)] = { 192, 64, TILE_WIDTH, TILE_HEIGHT };
}

void TileMap::Draw() const {
    for(const auto& pair : tiles) {
        // get the elements properties
        const Vector2i& cell = pair.first;
        SDL_Rect srcRect = pair.second;
        // translate tile position into world position
        Vector2i world = Math::CellToWorld(cell);
        // adjust position for camera position, I guess
        SDL_Rect destRect = { 
            transform.position.x + world.x,
            transform.position.y + world.y, 
            64, 
            32 
        };
        // Adjust position based on the camera
        destRect.x -= camera.getCameraRect().x;
        destRect.y -= camera.getCameraRect().y;
        // render the tile
        SDL_RenderCopy(g_resourceRepository.renderer, tile_texture, &srcRect, &destRect);
    }
}

void TileMap::HandleInput(InputEvent& event) {
    //if(event.handled) return;
}