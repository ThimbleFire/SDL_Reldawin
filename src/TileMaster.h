#ifndef _TILEMASTER_H_
#define _TILEMASTER_H_

#include "SceneObject.h"
#include "TileMap.h"
#include <map>

class TileMaster : public SceneObject {

    public:
        TileMaster() {}
        ~TileMaster() {}

        void CreateChunk(int w, int h) {
            TileMap* tileMap = new TileMap();
            for(int y = h * 16; y < (h + 1) * 16; y++)
            for(int x = w * 16; x < (w + 1) * 16; x++)
                tileMap->SetTile(x, y, 0);

            stuff[Vector2i(w, h)] = tileMap;
        }

        void CreateStartChunks(Vector2i chunk_position) {
            for(int x = chunk_position.x - 1; x < chunk_position.x + 2; x++) 
            for(int y = chunk_position.y - 1; y < chunk_position.y + 2; y++) {
                CreateChunk(x, y);
            }
        }

        void onChunkChange(Vector2i new_chunk, Vector2i last_chunk) {
            var directionOfTravel = new_chunk - last_chunk;
            for(int i = -1; i < 2; i++) {
                Vector2i offset_index = Vector2i(directionOfTravel.x == 0 ? i : directionOfTravel.x, directionOfTravel.y == 0 ? i : directionOfTravel.y);
                Vector2i create_index = new_chunk + offset_index;
                Vector2i remove_index = old_chunk - offset_index;
                replaceChunk(remove_index, create_index);
            }
        }

        void Draw() const override {
            for(const auto& pair : stuff) {
                pair.second->Draw();
            }
        }

        bool isOrthogonalDirection(Vector2i coordinates) {
            return coordinates.x == 1 && coordinates.y == 0 || coordinates.x == 0 && coordinates.y == 1 || coordinates.x == -1 && coordinates.y == 0 || coordinates.x == 0 && coordinates.y == -1;
        }
        bool isDiagonalDirection(coordinates : Vector2i) {
        	return coordinates == Vector2i::ONE || coordinates == -Vector2i::ONE || coordinates.x == 1 && coordinates.y == -1 || coordinates.x == -1 && coordinates.y == 1;
        }

        std::map<Vector2i, TileMap*> stuff;
};

#endif
