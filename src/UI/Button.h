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
            }
        }
        ~Button();

        void Draw() const override {
            destRect.x -= camera.getCameraRect().x;
            destRect.y -= camera.getCameraRect().y;
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &srcRect, &destRect);
        }

        void HandleInput(InputEvent& event) const override {
        }

        void dispose() const override {
        }
    private:
        SDL_Rect srcRect;
        SDL_Rect destRect;        
};

#endif
