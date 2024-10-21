#ifndef _MATH_H_
#define _MATH_H_

#include "defs.h"
#include "Vector2i.h"
#include <cmath>

class Math {
    public:
        //works
        static Vector2i WorldToIsometricWorld(Vector2i world) {
            int isoX = (world.x - world.y) * TILE_WIDTH_HALF;
            int isoY = (world.x + world.y) * TILE_HEIGHT_HALF;
            return Vector2i(isoX, isoY);
        }
        
        static Vector2i CellToWorld(int x, int y) {
            return CellToWorld(Vector2i(x, y));
        }
        static Vector2i CellToWorld(Vector2i cell) {
            float world_x = TILE_WIDTH_HALF * (cell.x - cell.y) + TILE_WIDTH_HALF;
            float world_y = TILE_HEIGHT_HALF * (cell.x + cell.y) + TILE_HEIGHT_HALF;
            return Vector2i(world_x, world_y);
        }
        static Vector2i WorldToCell(float x, float y) {
            return WorldToCell(Vector2i(x, y));
        }   
        //works
        static Vector2i WorldToCell(Vector2i world) {
            float cellX = (world.x / TILE_WIDTH + world.y / TILE_HEIGHT);
            float cellY = (world.y / TILE_HEIGHT - (world.x / TILE_WIDTH));
            return Vector2i(cellX, cellY);
        }
};

#endif