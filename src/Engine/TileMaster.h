#ifndef _TILEMASTER_H_
#define _TILEMASTER_H_

#include "SceneObject.h"
#include "TileMap.h"
#include <map>

class TileMaster : public SceneObject {
    SDL_Texture* texture;
    std::map<Vector2i, TileMap*> tileMaps;

    public:

        TileMaster(const std::string& path) {
            texture = g_resourceRepository.load(path);
        }   
        ~TileMaster() {
            SDL_DestroyTexture(texture);
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
            return {
                {node.x + 1, node.y},
                {node.x - 1, node.y},
                {node.x, node.y + 1},
                {node.x, node.y - 1},
                {node.x + 1, node.y + 1},
                {node.x - 1, node.y + 1},
                {node.x + 1, node.y - 1},
                {node.x - 1, node.y - 1}
            };
        }
        int heuristic(const Vector2& a, const Vector2& b) {
            int dx = std::abs(a.x - b.x);
            int dy = std::abs(a.y - b.y);
            return (dx > dy) ? (dy * 1.414) + (dx - dy) : (dx * 1.414) + (dy - dx);
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
            for (auto& chunk : tileMaps) {
                for (auto& nodePair : chunk.second->nodes) {
                    TileMap::Node& node = nodePair.second;
                    node.GCost = std::numeric_limits<int>::max();
                    node.HCost = 0;
                    node.parent = nullptr;
                }
            }

            TileMap::Node startNode = getNode(start);
            TileMap::Node endNode = getNode(end);

            std::vector<TileMap::Node*> openSet;
            std::vector<TileMap::Node*> closedSet;
            
            openSet.push_back(&startNode);

            startNode.GCost = 0;
            startNode.HCost = heuristic(startNode.position, endNode.position);

            while (!openSet.empty()) {
                // Sort openSet based on FCost (or pick the node with the lowest FCost)
                auto currentIt = std::min_element(openSet.begin(), openSet.end(),
                    [](TileMap::Node* a, TileMap::Node* b) {
                        return a->FCost() < b->FCost();
                    });
                
                TileMap::Node* currentNode = *currentIt;
                if (currentNode->cell == end) {
                    return reconstructPath(currentNode);
                }

                // Remove currentNode from openSet and add to closedSet
                openSet.erase(currentIt);
                closedSet.push_back(currentNode);

                for (auto& neighborPos : getNeighbors(currentNode->cell)) {
    TileMap::Node* neighbor = &getNode(neighborPos);

    if (neighbor->parent == nullptr) {
        neighbor->GCost = std::numeric_limits<int>::max(); // Reset node state
        neighbor->HCost = 0;
    }

    if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
        continue; // Skip if the neighbor is in the closed set
    }

    // Determine if the move is diagonal or straight
    int moveCost = (std::abs(neighborPos.x - currentNode->cell.x) == 1 &&
                    std::abs(neighborPos.y - currentNode->cell.y) == 1) 
                    ? 1.414 // Diagonal move
                    : 1;    // Straight move

    int tentativeGCost = currentNode->GCost + moveCost;

    if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
        openSet.push_back(neighbor);
    } else if (tentativeGCost >= neighbor->GCost) {
        continue; // If not a better path, skip
    }

    // Update neighbor
    neighbor->parent = currentNode;
    neighbor->GCost = tentativeGCost;
    neighbor->HCost = heuristic(neighbor->position, endNode.position);
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
