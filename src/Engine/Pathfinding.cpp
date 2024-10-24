#include "Pathfinding.h"

Pathfinding g_pathfinder;

Pathfinding::Pathfinding(const std::map<Vector2i, TileMap*> maps) {
    int index = 0;
    for(const auto& pair : maps) {
        this->maps[index++] = pair.second;
    }
}
Pathfinding::~Pathfinding() {}
void Pathfinder::CalculatePath(Vector2i start, Vector2i end) {

}
