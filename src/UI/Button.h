#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button : public UIElement {
    public:
        Button(Transform* parentTransform) {
            this->parentTransform = parentTransform;
            destRect = { 
                transform.position.x + parentTransform->position.x, 
                transform.position.y + parentTransform->position.y, 
                Size.x, 
                Size.y 
            };
            srcRect = { 
                0, 
                0, 
                32, 
                32 
            };
        }

        void Draw() const override {
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &srcRect, &destRect);
        }

        void HandleInput(InputEvent& event) const override {
            if(event.handled) return;
            
            SDL_Point point = { event.screen.x, event.screen.y };
            if (SDL_PointInRect(&point, &destRect)) {
                printf("Clicked!\n");
                event.handled = true;
            }
        }
    private:
        SDL_Rect srcRect;
        SDL_Rect destRect;        
};

#endif
