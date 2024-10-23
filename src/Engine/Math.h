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
            float W_x = world.x;
            float W_y = world.y;

            float x = (W_x / TILE_WIDTH_HALF + W_y / TILE_HEIGHT_HALF) / 2.0;
            float y = (W_y / TILE_HEIGHT_HALF - W_x / TILE_WIDTH_HALF) / 2.0;

            x = floor(x + 0.5);
            y = floor(y + 0.5);
            return Vector2i(x, y);
        }
        static float radiansToDegrees(float radians) {
            return radians * (180.0 / 3.14159265358979323846);
        }
};

#endif
