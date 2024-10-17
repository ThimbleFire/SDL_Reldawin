#ifndef _MATH_H_
#define _MATH_H_

#include "defs.h"
#include "Vector2i.h"
#include "Vector2.h"
#include <cmath>

class Math {
    public:
        static Vector2 CellToWorld(int x, int y) {
            return CellToWorld(Vector2i(x, y));
        }
        static Vector2 CellToWorld(Vector2i cell) {
            float world_x = TILE_WIDTH_HALF * (cell.x - cell.y) + TILE_WIDTH_HALF;
            float world_y = TILE_HEIGHT_HALF * (cell.x + cell.y) + TILE_HEIGHT_HALF;
            return Vector2(world_x, world_y);
        }
        static Vector2i WorldToCell(float x, float y) {
            return WorldToCell(Vector2(x, y));
        }
        static Vector2i WorldToCell(Vector2 world) {
            float w_x = world.x - TILE_WIDTH_HALF;
            float w_y = world.y - TILE_HEIGHT_HALF;
            float x = (w_x / 32 + w_y / 16) / 2.0f;
            float y = (w_y / 16 - w_x / 32) / 2.0f;
            x = std::floor(x + 0.5f);
            y = std::floor(y + 0.5f);
            return Vector2i(x, y);
        }
};

#endif

// static func world_to_cell(world_coordinates: Vector2) -> Vector2:
// 	const origin_x = 32
// 	const origin_y = 16
// 	var W_x = world_coordinates.x - origin_x
// 	var W_y = world_coordinates.y - origin_y
// 	var x = (W_x / 32.0 + W_y / 16.0) / 2.0
// 	var y = (W_y / 16.0 - W_x / 32.0) / 2.0
// 	x = floor(x + 0.5)
// 	y = floor(y + 0.5)
// 	return Vector2(x, y)