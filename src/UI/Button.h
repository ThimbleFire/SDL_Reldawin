#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button : public UIElement {
    public:
        void HandleInput(InputEvent& event) const override {
            if(event.handled) return;
            
            SDL_Point point = { event.screen.x, event.screen.y };
            if (SDL_PointInRect(&point, &destRect)) {
                printf("Clicked!\n");
                event.handled = true;
            }
        }    
};

#endif
