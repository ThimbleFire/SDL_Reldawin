#ifndef _MATH_H_
#define _MATH_H_

#include "defs.h"
#include "Vector2i.h"
#include <cmath>

class Math {
    public:
        static Vector2 CellToWorld(int x, int y) {
            return CellToWorld(Vector2i(x, y));
        }
        static Vector2 CellToWorld(Vector2i cell) {            
            return Vector2(TILE_WIDTH_HALF  * (cell.x - cell.y), 
                           TILE_HEIGHT_HALF * (cell.x + cell.y));
        }
        static Vector2i WorldToCell(float x, float y) {
            return WorldToCell(Vector2(x, y));
        }   
        static Vector2i WorldToCell(Vector2 world) {
            float x = (world.x / TILE_WIDTH_HALF + world.y / TILE_HEIGHT_HALF) / 2.0f;
            float y = (world.y / TILE_HEIGHT_HALF - world.x / TILE_WIDTH_HALF) / 2.0f;
            return Vector2i(x, y);
        }
        static float radiansToDegrees(float radians) {
            return radians * (180.0 / M_PI);
        }

    public:
        const double M_PI = 3.14159265358979323846;
};

#endif
