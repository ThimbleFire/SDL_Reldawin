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
        static Vector2i WorldToCell(Vector2i world) {
            Vector2 vec = world.ToVec2();
            float w_x = vec.x - TILE_WIDTH_HALF;
            float w_y = vec.y - TILE_HEIGHT_HALF;
            float x = (w_x / TILE_WIDTH_HALF + w_y / TILE_HEIGHT_HALF) / 2.0f;
            float y = (w_y / TILE_HEIGHT_HALF - w_x / TILE_WIDTH_HALF) / 2.0f;
            x = std::floor(x - 0.5f);
            y = std::floor(y + 0.5f);
            return Vector2i(x, y);
        }
};

#endif