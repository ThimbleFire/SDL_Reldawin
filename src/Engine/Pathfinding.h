#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_

#include <vector>
#include <map>
#include "Vector2i.h"
#include "TileMap.h"
#include "TileMaster.h"

class Pathfinding {
    public:
        Pathfinding(TileMaster* tMaster) : tileMaster(tMaster);
        ~Pathfinding();
        void GetPath();

    public:
        TileMaster* tileMaster;
};

extern Pathfinding g_pathfinder;

#endif
