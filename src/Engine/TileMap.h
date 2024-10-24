#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include <SDL2/SDL_rect.h>
#include <map>
#include "SceneObject.h"
#include "Camera.h"
#include "ResourceRepository.h"

class TileMap : public SceneObject {
    public:
        struct Node {
            Vector2i position;
            Node* parent = nullptr;
            int GCost;
            int HCost;
            int FCost() const { 
                return GCost + HCost; 
            }
        
            Node(Vector2i pos) : 
                position(pos), 
                GCost(0), 
                HCost(0) {
                
                }
        };
    public:
        TileMap();
        ~TileMap();
        void CreateChunk(int w, int h);
        void CreateChunk(int w, int h, SDL_Texture* texture);
        void SetTile(int x, int y, int8_t id);        
        void Draw() const override;
        void HandleInput(InputEvent& event) override;
        void clear() {
            tiles.clear();
        }
    private:
        SDL_Texture* tile_texture;
        std::map<Vector2i, SDL_Rect> tiles;
        std::map<Vector2i, Node> nodes;

};

#endif
