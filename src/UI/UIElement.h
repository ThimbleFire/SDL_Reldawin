#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

#include "SceneObject.h"
#include "ResourceRepository.h"

class UIElement : public SceneObject {
    public:
        UIElement(Transform* parentTransform) {
            spritesheet = g_resourceRepository.load("res/UI.png");
            parentTransform = parentTransform;
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
            
        }

        void dispose() const override {
            
        }

    public:
        int flag = -1;

    protected:
        Vector2i Size;
        Transform* parentTransform;
        SDL_Texture* spritesheet;
        SDL_Rect srcRect;
        SDL_Rect destRect;  
};

#endif
