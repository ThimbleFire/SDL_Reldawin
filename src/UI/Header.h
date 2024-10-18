#ifndef _HEADER_H_
#define _HEADER_H_

#include "UIElement.h"

class Header : public UIElement {
    public:
        bool dragging = false;
        void HandleInput(InputEvent& event) const override {
            if(event.handled) return;
            
            SDL_Point point = { event.screen.x, event.screen.y };
            if (SDL_PointInRect(&point, &destRect)) {
                printf("Clicked!\n");
                event.handled = true;
                dragging = true;
            }
        } 
};

#endif
