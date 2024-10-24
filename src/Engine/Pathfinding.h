#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_

#include <vector>
#include <array>
#include <set>
#include <queue>
#include "TileMaster.h"
#include "Vector2i.h"



class Pathfinding {
    public:
        struct Node {
            TileMap* tileMap;
            Vector2i position_local;
            
            Vector2i position_global() const { 
                return tileMap->index * CHUNK_SIZE + position_local;
            }
            
            Node* parent = nullptr;
            int GCost;
            int HCost;
            int FCost() const { 
                return GCost + HCost; 
            }
        
            Node(TileMap* tileMap, Vector2i pos) : 
                tileMap(tileMap),
                position_local(pos), 
                GCost(0), 
                HCost(0) {
                
                }
        };
    public:
    ~Pathfinding() {
        for (auto& pair : nodes) {
            delete pair.second;
        }
    }

    void initialize(const std::unordered_map<Vector2i, TileMap*> tileMaps) {
        for (const auto tileMapPair : tileMaps) {
            TileMap* tileMap = tileMapPair.second;
            for (int y = 0; y < CHUNK_SIZE; y++) {
                for (int x = 0; x < CHUNK_SIZE; x++) {
                    Vector2i localPosition(x, y);
                    nodes[tileMap.index + localPosition] = new Node(tileMap, localPosition, nullptr);
                }
            }
        }
    }

    public:
        static std::unordered_map<Vector2i, Node*> nodes;
};

extern Pathfinding g_pathfinder;

#endif
