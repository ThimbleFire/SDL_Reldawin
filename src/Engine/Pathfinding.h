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
            
            Node* parent;
            int GCost; // Cost from start to this node
            int HCost; // Heuristic cost to end
            int FCost() const { 
                return GCost + HCost; 
            }
        
            Node(Vector2i pos, Node* parentNode) : 
                position(pos), 
                parent(parentNode), 
                GCost(0), 
                HCost(0) {
                
                }
        };
    public:

    void initialize(const std::unordered_map<Vector2i, TileMap*>& tileMaps) {
        for (const auto& tileMapPair : tileMaps) {
            TileMap* tileMap = tileMapPair.second;
            for (int y = 0; y < CHUNK_SIZE; y++) {
                for (int x = 0; x < CHUNK_SIZE; x++) {
                    Vector2i tilePosition = tile.first;
                    nodes[tileMap.index + Vector2i(x, y)] = new Node(tilePosition, nullptr);
                }
            }
            
        }
    }

    public:
        static std::unsorted_map<Vector2i, Node*> nodes;
};

extern Pathfinding g_pathfinder;

#endif
