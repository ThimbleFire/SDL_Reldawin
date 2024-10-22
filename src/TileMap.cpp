#include "TileMap.h"
#include "Math.h"

SDL_Texture* tile_texture;

TileMap::TileMap() {
    tile_texture = g_resourceRepository.load("res/tile.png");
}

TileMap::~TileMap() {
    g_resourceRepository.unload("res/tile.png");
}

void TileMap::CreateChunk(int w, int h) {
    for(int y = h * 16; y < (h + 1) * 16; y++)
    for(int x = w * 16; x < (w + 1) * 16; x++)
        SetTile(x, y, 0);
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
        Vector2 world = Math::CellToWorld(cell);
        SDL_FRect cameraRect = camera.ToRect();
        // adjust position for camera position, I guess
        SDL_FRect destRect = { 
            transform.position.x + world.x - cameraRect.x,
            transform.position.y + world.y - cameraRect.y, 
            TILE_WIDTH,
            TILE_HEIGHT 
        };
        // render the tile
        SDL_RenderCopyF(g_resourceRepository.renderer, tile_texture, &srcRect, &destRect);
    }
}

void TileMap::HandleInput(InputEvent& event) {
    //if(event.handled) return;
}
