#ifndef _MATH_H_
#define _MATH_H_

#include "defs.h"
#include "Vector2i.h"
#include <cmath>

class Math {
    public:
        //works
        static Vector2 WorldToIsometricWorld(Vector2 world) {
            float isoX = (world.x - world.y) * TILE_WIDTH_HALF;
            float isoY = (world.x + world.y) * TILE_HEIGHT_HALF;
            return Vector2(isoX, isoY);
        }
        static Vector2 CellToWorld(int x, int y) {
            return CellToWorld(Vector2i(x, y));
        }
        static Vector2 CellToWorld(Vector2i cell) {            
            return Vector2(TILE_WIDTH_HALF * (cell.x - cell.y) + TILE_WIDTH_HALF, TILE_HEIGHT_HALF * (cell.x + cell.y) + TILE_HEIGHT_HALF);
        }
        static Vector2i WorldToCell(float x, float y) {
            return WorldToCell(Vector2(x, y));
        }   
        static Vector2i WorldToCell(Vector2 world) {
            float w_x = world.x - TILE_WIDTH_HALF;
            float w_y = world.y - TILE_HEIGHT_HALF;
            float x = (w_x / TILE_WIDTH_HALF + w_y / TILE_HEIGHT_HALF) / 2.0f;
            float y = (w_y / TILE_HEIGHT_HALF - w_x / TILE_WIDTH_HALF) / 2.0f;
            return Vector2i(x, y);
        }
};

#endif