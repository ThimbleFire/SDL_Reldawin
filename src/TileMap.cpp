#include "TileMap.h"
#include "Math.h"

TileMap::TileMap() {

}

TileMap::~TileMap() {

}

void TileMap::SetTile(int x, int y, int8_t id) {
    
    SDL_Texture* tile_texture = g_resourceRepository.load("res/tile.png");
    tiles[Vector2i(x, y)] = tile_texture;
    Vector2 world = Math::CellToWorld(x, y);
    std::cout << std::to_string(world.x) + ", " + std::to_string(world.y) << std::endl;
}


void TileMap::Draw() const {
    for(const auto& pair : tiles) {
        // get the elements properties
        const Vector2i& cell = pair.first;
        SDL_Texture* texture = pair.second;
        // translate tile position into world position
        Vector2 world = Math::CellToWorld(cell);
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
        SDL_RenderCopy(g_resourceRepository.renderer, texture, nullptr, &destRect);
    }
}