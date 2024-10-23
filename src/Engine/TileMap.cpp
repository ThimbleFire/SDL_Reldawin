#include "TileMap.h"
#include "Math.h"

// Headers for loading a .csv file containing map data
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SDL_Texture* tile_texture;

TileMap::TileMap() {
    tile_texture = g_resourceRepository.load("res/tile.png");
}

TileMap::~TileMap() {
    g_resourceRepository.unload("res/tile.png");
}

void TileMap::CreateChunk(int w, int h, SDL_Texture* texture) {
    this->tile_texture = texture;
    CreateChunk(w, h);
}
// Method for loading .csv map data
void TileMap::CreateChunk(int w, int h) {
    // Construct the file name based on the chunk coordinates
    std::string filename = "chunk_" + std::to_string(w) + "_" + std::to_string(h) + ".csv";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << ". Loading NULL chunk." << std::endl;    
        for(int y = h * 16; y < (h + 1) * 16; y++)
        for(int x = w * 16; x < (w + 1) * 16; x++)
            SetTile(x, y, 0);
        return;
    }
    std::string line;
    int tileY = h * 16; // Start Y position for the chunk
    // Reading each line from the file (each line represents a row of tiles)
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        int tileX = w * 16; // Start X position for the chunk
        // Split line by commas (representing tile IDs in the row)
        while (std::getline(lineStream, cell, ',')) {
            int id = std::stoi(cell);  // Convert the string to a tile ID (int)
            SetTile(tileX, tileY, id); // Set the tile at the current position
            tileX++; // Move to the next tile in the row
        }
        tileY++; // Move to the next row
    }
    file.close();
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
            transform.position.x + // transform.position should be be { 0, 0 }
            world.x - // world offset will be the location of the tile, ie (cell.x * chunk.x) to world space
            TILE_WIDTH_HALF - // tile is offset because otherwise { 0, 0 } is the topleft of the rectangle
            cameraRect.x,// then offset the rectangle by the cameraRect so we're rendering what's on camera
            transform.position.y + world.y - TILE_HEIGHT_HALF - cameraRect.y, 
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
