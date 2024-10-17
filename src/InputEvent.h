#ifndef _INPUTEVENT_H_
#define _INPUTEVENT_H_

#include "Camera.h"
#include "Math.h"
#include "Vector2i.h"
#include "Vector2.h"

class InputEvent {
    public:
        InputEvent(int x, int y) {
            screen = Vector2i(x, y);
            world = camera.ScreenToWorld(x, y);
            cell = Math::WorldToCell(world.x, world.y);
        } 
    
    public:
        Vector2i screen;
        Vector2 world;
        Vector2i cell;
        bool handled = false; 
};

#endif