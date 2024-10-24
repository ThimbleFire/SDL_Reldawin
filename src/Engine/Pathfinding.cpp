#include "Pathfinding.h"
#include "TileMaster.h"

Pathfinding g_pathfinder;

Pathfinding::Pathfinding(TileMaster* tMaster) : tileMaster(tMaster) {}

Pathfinding::~Pathfinding() {}

std::vector<Vector2i> Pathfinder::GetPath(Vector2i start, Vector2i end) {
    std::priority_queue<Node*, std::vector<Node*>, 
        std::function<bool(Node*, Node*)>> openSet(
            [](Node* a, Node* b) { return a->FCost() > b->FCost(); });

    std::set<Vector2i> closedSet;

    Node* startNode = new Node(start);
    openSet.push(startNode);

    while (!openSet.empty()) {
        Node* currentNode = openSet.top();
        openSet.pop();

        if (currentNode->position == end) {
            // Retrace path
            std::vector<Vector2i> path;
            Node* pathNode = currentNode;

            while (pathNode) {
                path.push_back(pathNode->position);
                pathNode = pathNode->parent;
            }

            std::reverse(path.begin(), path.end());
            // Return or process the path as needed (e.g., store in a member variable)

            // Cleanup
            delete currentNode;
            return path;
        }

        closedSet.insert(currentNode->position);

        // Check neighbors (4 directions: up, down, left, right)
        Vector2i directions[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        for (const auto& dir : directions) {
            Vector2i neighborPos = currentNode->position + dir;

            // Check if the neighbor is in bounds and not occupied
            bool validNeighbor = false;
            if(tileMaster->tilemaps[neighbourPos/CHUNK_SIZE]) {
                validNeighbor = true;
            }
            if (!validNeighbor || closedSet.count(neighborPos)) {
                continue; // Skip if invalid or already evaluated
            }

            int newGCost = currentNode->GCost + 1; // Assume uniform cost for simplicity
            Node* neighborNode = new Node(neighborPos, currentNode);

            if (newGCost < neighborNode->GCost || 
                std::find_if(openSet.c.begin(), openSet.c.end(), [&](Node* n) { return n->position == neighborPos; }) == openSet.c.end()) {
                neighborNode->GCost = newGCost;
                neighborNode->HCost = Heuristic(neighborPos, end);
                openSet.push(neighborNode);
            } else {
                delete neighborNode; // Avoid memory leak if we don't need this node
            }
        }

        delete currentNode; // Cleanup current node
    }
}
