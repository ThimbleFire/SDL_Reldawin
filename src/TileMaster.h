#ifndef _TILEMASTER_H_
#define _TILEMASTER_H_

#include "SceneObject.h"
#include "TileMap.h"
#include <map>

class TileMaster : public SceneObject {

    public:
        TileMaster() {}
        ~TileMaster() {}

        void CreateStartChunks(Vector2i chunk_position) {
            for(int x = chunk_position.x - 1; x < chunk_position.x + 2; x++) 
            for(int y = chunk_position.y - 1; y < chunk_position.y + 2; y++) {
                TileMap* tileMap = new TileMap();
                stuff[Vector2i(x, y)] = tileMap;
                stuff[Vector2i(x, y)].CreateChunk(x, y);
            }
        }

        void onChunkChange(Vector2i new_chunk, Vector2i last_chunk) {
            var directionOfTravel = new_chunk - last_chunk;
            if (isOrthogonalDirection(directionOfTravel)) {
                for(int i = -1; i < 2; i++) {
                    Vector2i offset_index = Vector2i(directionOfTravel.x == 0 ? i : directionOfTravel.x, directionOfTravel.y == 0 ? i : directionOfTravel.y);
                    Vector2i create_index = new_chunk + offset_index;
                    Vector2i remove_index = last_chunk - offset_index;
                    replaceChunk(remove_index, create_index);
                }
            }
            else if (isDiagonalDirection(directionOfTravel)) {
                for(int i = 0; i < 3; i++) {
                    Vector2i offset_index = Vector2i(directionOfTravel.x == 1 ? -i : i, directionOfTravel.y == 1 ? -i : i);
                    Vector2i remove_indexX = (last_chunk - directionOfTravel) - Vector2i(offset_index.x, 0);
                    Vector2i remove_indexY = (last_chunk - directionOfTravel) - Vector2i(0, offset_index.y);
                    Vector2i create_indexX = new_chunk + directionOfTravel + Vector2i(offset_index.x, 0);
                    Vector2i create_indexY = new_chunk + directionOfTravel + Vector2i(0, offset_index.y);
                    replaceChunk(remove_indexX, create_indexY);
                    replaceChunk(remove_indexY, create_indexY);
                }
            }
        }

        void replaceChunk(Vector2i old_chunk, Vector2i new_chunk) {
            stuff[old_chunk]->tiles.clear();
            stuff[new_chunk] = stuff[old_chunk];
            stuff.erase(old_chunk);
            stuff[new_chunk].CreateChunk(new_chunk.x, new_chunk.y);
            std::cerr << "replaced " old_chunk.ToString() + " with " + new_chunk.ToString() << std::endl;
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
