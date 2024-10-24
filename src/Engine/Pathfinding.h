#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_

#include <vector>
#include <map>
#include "Vector2i.h"
#include "TileMap.h"

class Pathfinding {
    public:
        Pathfinding(std::map<Vector2i, TileMap*> maps);
        ~Pathfinding();
        void GetPath();

    public:
        std::array<TileMap*, 9> maps;
};

extern Pathfinding g_pathfinder;

#endif
