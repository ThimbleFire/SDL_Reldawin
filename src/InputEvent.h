#ifndef _INPUTEVENT_H_
#define _INPUTEVENT_H_

#include "Camera.h"
#include "Math.h"
#include "Vector2i.h"
#include "Vector2.h"

class InputEvent {
    public:
        enum Type { NONE, LMB_PRESSED, LMB_RELEASED, RMB_PRESSED, RMB_RELEASED }

    public:
        InputEvent(int x, int y, Type type) : type{type) {
            screen = Vector2i(x, y);
            world = camera.ScreenToWorld(x, y);
            cell = Math::WorldToCell(world.x, world.y);
        } 
    
    public:
        readonly Vector2i screen;
        readonly Vector2 world;
        readonly Vector2i cell;
        bool handled = false;
        readonly Type type = Type.NONE;
};

#endif
