#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "SceneObject.h"

class Entity : public SceneObject {
    public:
        Entity() {};
        ~Entity() {};

        void Draw() const override;
        void Update() override;

        Vector2i cell_global() const {
            return Math::WorldToCell(transform.position);
        }
        Vector2i chunk_position() const {
            Vector2i cell = cell_global();
            return Vector2i(cell.x / CHUNK_SIZE, cell.y / CHUNK_SIZE);
        }
        void makePath(Vector2i cell);
        void clearPath();
    protected:
        virtual void onTileChanged(Vector2i cellGlobalLast, Vector2i cellGlobalCurrent);
        virtual void onChunkChanged(Vector2i chunkPositionLast, Vector2i chunkPositionCurrent);
        virtual void onDestinationReached();
    public:
        Event on_destination_reached;
        bool isMoving = false;
    private:
        void updateAnimationDirection();

    protected:
        std::vector<Vector2i> pathfinding_chain;
};

#endif
