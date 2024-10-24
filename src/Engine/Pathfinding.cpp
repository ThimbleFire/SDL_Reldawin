#include "Pathfinding.h"
#include "TileMaster.h"

Pathfinding g_pathfinder;

Pathfinding::Pathfinding(TileMaster* tMaster) : tileMaster(tMaster) {}
Pathfinding::~Pathfinding() {}
void Pathfinder::GetPath(Vector2i start, Vector2i end) {

}
