#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_

#include <vector>
#include <map>
#include "Vector2i.h"
#include "Tile.h"
#include "TileMap.h"

class Pathfinding {
    public:
        Pathfinding();
        ~Pathfinding();
        void populate(std::map<Vector2i, TileMap*> stuff);
};

extern Pathfinding g_pathfinder;

#endif