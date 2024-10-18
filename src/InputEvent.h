#ifndef _INPUTEVENT_H_
#define _INPUTEVENT_H_

#include "Camera.h"
#include "Math.h"
#include "Vector2i.h"
#include "Vector2.h"

class InputEvent {
    public:
        InputEvent(SDL_Event event) : event(event) {   
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    screen = Vector2i(event.button.x, event.button.y);
                    world = camera.ScreenToWorld(event.button.x, event.button.y);
                    cell = Math::WorldToCell(world.x, world.y);
                break;
                case SDL_MOUSEMOTION:
                    screen = Vector2i(event.motion.x, event.motion.y);
                    world = camera.ScreenToWorld(event.motion.x, event.motion.y);
                    cell = Math::WorldToCell(world.x, world.y);
                break;
            }                    
        } 
    
    public:
        Vector2i screen;
        Vector2 world;
        Vector2i cell;

        bool handled = false;
        SDL_Event event;
};

#endif
