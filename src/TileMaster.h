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

        void Draw() const override {
            for(const auto& pair : stuff) {
                pair.second->Draw();
            }
        }

        std::map<Vector2i, TileMap*> stuff;
};

#endif