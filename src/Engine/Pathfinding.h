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
            Vector2i position;
            Node* parent;
            int GCost; // Cost from start to this node
            int HCost; // Heuristic cost to end
            int FCost() const { return GCost + HCost; }
        
            Node(Vector2i pos, Node* parentNode) : position(pos), parent(parentNode), GCost(0), HCost(0) {}
        };
        struct Vector2iComparator {
            bool operator()(const Vector2i& a, const Vector2i& b) const {
                if (a.x != b.x) return a.x < b.x; // Sort by x first
                return a.y < b.y;                 // Then sort by y
            }
        };
    public:
        void populate(std::map<Vector2i, TileMap*, Vector2iComparator> tileMaps) {
            for (auto& tileMap : tileMaps) {
                //
            }
        }

    public:
        static std::map<Vector2i, Node*> nodes;
};

extern Pathfinding g_pathfinder;

#endif
