#include "Pathfinding.h"

Pathfinding g_pathfinder;

struct Vector2iHash {
    size_t operator()(const Vector2i& v) const {
        return hash<int>()(v.x) ^ hash<int>()(v.y);
    }
};

unordered_map<Vector2i, Node*, Vector2iHash> nodes;

Pathfinding::Pathfinding() {

}

Pathfinding::~Pathfinding() {

}

void Pathfinding::populate(std::map<Vector2i, TileMap*> tilemaps){
    for (const auto& tilemap : tilemaps) {
        for (const auto& n : tilemap.second->tiles) {
            Vector2i worldPos = n.first;
            //nodes[worldPos] = n.get();  // Use raw pointer of unique_ptr for the map
        }
    }
}
