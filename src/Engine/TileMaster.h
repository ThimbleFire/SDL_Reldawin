#ifndef _TILEMASTER_H_
#define _TILEMASTER_H_

#include "SceneObject.h"
#include "TileMap.h"
#include <map>

class TileMaster : public SceneObject {
    SDL_Texture* texture;
    std::map<Vector2i, TileMap*> tileMaps;
    std::unordered_set<TileMap::Node*> touchedNodes;

    public:

        TileMaster(const std::string& path) {
            texture = g_resourceRepository.load(path);
        }   
        ~TileMaster() {
            SDL_DestroyTexture(texture);    
            for (auto& chunkPair : tileMaps) {
                delete chunkPair.second;
            }
            touchedNodes.clear();
            tileMaps.clear();
        }
        void CreateStartChunks(Vector2i chunk_position) {
            for(int x = chunk_position.x - 1; x < chunk_position.x + 2; x++) 
            for(int y = chunk_position.y - 1; y < chunk_position.y + 2; y++) {
                TileMap* tileMap = new TileMap();
                tileMaps[Vector2i(x, y)] = tileMap;
                tileMaps[Vector2i(x, y)]->CreateChunk(x, y, texture);
            }
        }
        void onChunkChange(Vector2i new_chunk, Vector2i old_chunk) {
            Vector2i directionOfTravel = new_chunk - old_chunk;
            if (isOrthogonalDirection(directionOfTravel)) {
                for(int i = -1; i < 2; i++) {
                    Vector2i offset_index = Vector2i(directionOfTravel.x == 0 ? i : directionOfTravel.x, directionOfTravel.y == 0 ? i : directionOfTravel.y);
                    Vector2i create_index = new_chunk + offset_index;
                    Vector2i remove_index = old_chunk - offset_index;
                    replaceChunk(remove_index, create_index);
                }
            }
            else if (isDiagonalDirection(directionOfTravel)) {
                for(int i = 0; i < 3; i++) {
                    Vector2i offset_index = Vector2i(directionOfTravel.x == 1 ? -i : i, directionOfTravel.y == 1 ? -i : i);
                    Vector2i remove_indexX = (old_chunk - directionOfTravel) - Vector2i(offset_index.x, 0);
                    Vector2i remove_indexY = (old_chunk - directionOfTravel) - Vector2i(0, offset_index.y);
                    Vector2i create_indexX = new_chunk + directionOfTravel + Vector2i(offset_index.x, 0);
                    Vector2i create_indexY = new_chunk + directionOfTravel + Vector2i(0, offset_index.y);
                    replaceChunk(remove_indexX, create_indexX);
                    
                    if(i > 0)
                        replaceChunk(remove_indexY, create_indexY);
                }
            }
        }
        void replaceChunk(Vector2i old_chunk, Vector2i new_chunk) {
            tileMaps[old_chunk]->clear();
            tileMaps[new_chunk] = tileMaps[old_chunk];
            tileMaps.erase(old_chunk);
            if(new_chunk.x >= 0 && new_chunk.y >= 0) {
                tileMaps[new_chunk]->CreateChunk(new_chunk.x, new_chunk.y);
            }
        }
        bool isOrthogonalDirection(Vector2i coordinates) {
            return coordinates.x == 1 && coordinates.y == 0 || coordinates.x == 0 && coordinates.y == 1 || coordinates.x == -1 && coordinates.y == 0 || coordinates.x == 0 && coordinates.y == -1;
        }
        bool isDiagonalDirection(Vector2i coordinates) {
        	return coordinates == Vector2i::ONE || coordinates == -Vector2i::ONE || coordinates.x == 1 && coordinates.y == -1 || coordinates.x == -1 && coordinates.y == 1;
        }

        std::vector<Vector2i> getNeighbors(Vector2i node) {
            std::vector<Vector2i> neighbors;
        
            std::vector<Vector2i> possibleNeighbors = {
                {node.x + 1, node.y},      // Right
                {node.x - 1, node.y},      // Left
                {node.x, node.y + 1},      // Down
                {node.x, node.y - 1},      // Up
                {node.x + 1, node.y + 1},  // Bottom-right (Diagonal)
                {node.x - 1, node.y + 1},  // Bottom-left (Diagonal)
                {node.x + 1, node.y - 1},  // Top-right (Diagonal)
                {node.x - 1, node.y - 1}   // Top-left (Diagonal)
            };
        
            for (auto& neighbor : possibleNeighbors) {
                if (isValidTile(neighbor)) { // Assuming isValidTile checks bounds and obstacles
                    neighbors.push_back(neighbor);
                }
            }
        
            return neighbors;
        }
        // Comparator for priority queue (min-heap) based on FCost
        struct CompareNodeFCost {
            bool operator()(TileMap::Node* a, TileMap::Node* b) {
                return a->FCost() > b->FCost(); // Min-heap, so the node with lower FCost comes first
            }
        };
        
        int heuristic(const Vector2& a, const Vector2& b) {
            int dx = std::abs(a.x - b.x);
            int dy = std::abs(a.y - b.y);
            return (dx > dy) ? (dy * 14) + (dx - dy) * 10 : (dx * 14) + (dy - dx) * 10;
        }
        
        std::vector<Vector2> reconstructPath(TileMap::Node* endNode) {
            std::vector<Vector2> path;
            TileMap::Node* current = endNode;
            while (current != nullptr) {
                path.push_back(current->position);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        std::vector<Vector2> getPath(Vector2i start, Vector2i end) {
            // Reset only the nodes that were touched in the previous pathfinding run
            for (TileMap::Node* node : touchedNodes) {
                node->GCost = std::numeric_limits<int>::max();
                node->HCost = 0;
                node->parent = nullptr;
            }
            touchedNodes.clear();  // Clear the set after resetting nodes
        
            TileMap::Node& startNode = getNode(start);
            TileMap::Node& endNode = getNode(end);
        
            std::priority_queue<TileMap::Node*, std::vector<TileMap::Node*>, CompareNodeFCost> openSet;
            std::unordered_set<TileMap::Node*> closedSet;
        
            // Push the start node into the open set (min-heap priority queue)
            openSet.push(&startNode);
            startNode.GCost = 0;
            startNode.HCost = heuristic(startNode.position, endNode.position);
            
            touchedNodes.insert(&startNode);
        
            while (!openSet.empty()) {
                TileMap::Node* currentNode = openSet.top(); // Get node with the lowest FCost
                openSet.pop();
        
                if (currentNode->cell == end) {
                    return reconstructPath(currentNode); // Path found
                }
        
                closedSet.insert(currentNode); // Add to closed set
                touchedNodes.insert(currentNode);
        
                for (auto& neighborPos : getNeighbors(currentNode->cell)) {
                    TileMap::Node* neighbor = &getNode(neighborPos);
        
                    if (closedSet.find(neighbor) != closedSet.end()) {
                        continue; // Skip if the neighbor is already in the closed set
                    }
        
                    // Determine if the move is diagonal or straight
                    int moveCost = heuristic(currentNode->position, neighbor->position);
                    int tentativeGCost = currentNode->GCost + moveCost;
        
                    // If this is a better path or the node hasn't been processed yet
                    if (tentativeGCost < neighbor->GCost) {
                        neighbor->parent = currentNode;
                        neighbor->GCost = tentativeGCost;
                        neighbor->HCost = heuristic(neighbor->position, endNode.position);
        
                        // Add to the open set if not already in it
                        if (std::find_if(openSet.begin(), openSet.end(), 
                            [neighbor](TileMap::Node* node) { return node == neighbor; }) == openSet.end()) {
                            openSet.push(neighbor);
                        }

                        touchedNodes.insert(neighbor);
                    }
                }
            }
        
            return {}; // No path found
        }
        
        TileMap::Node& getNode(Vector2i tile) {
            return tileMaps[tile / CHUNK_SIZE]->nodes[tile];
        }

        void Draw() const override {
            for(const auto& pair : tileMaps) {
                pair.second->Draw();
            }
        }
};

#endif
