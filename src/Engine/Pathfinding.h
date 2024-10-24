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
    public:
        Pathfinding(TileMaster* tMaster) : tileMaster(tMaster);
        ~Pathfinding();
        void GetPath();

    public:
        TileMaster* tileMaster;
};

extern Pathfinding g_pathfinder;

#endif
