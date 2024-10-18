#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "UIElement.h"

class UIButton : public UIElement {
    public:
        UIButton(Transform& parentTransform) : UIElement(parentTransform) { }
        void HandleInput(InputEvent& event) override {
            if(event.handled) return;
            
            SDL_Point point = { event.screen.x, event.screen.y };
            if (SDL_PointInRect(&point, &destRect)) {
                printf("Clicked!\n");
                event.handled = true;
            }
        }
};

#endif
