#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

#include "SceneObject.h"
#include "ResourceRepository.h"

class UIElement : public SceneObject {
    public:
        UIElement(Transform& parentTransform) : parentTransform(parentTransform) {
            destRect = { 
                transform.position.x + parentTransform.position.x, 
                transform.position.y + parentTransform.position.y, 
                100, 100
            };
        }

        void Draw() const override {
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &srcRect, &destRect);
        }

        void HandleInput(InputEvent& event) override {}
        void dispose() const override {}
        void setTexture(SDL_Texture* texture) {
            spritesheet = texture;
        }
        virtual void setSize(int x, int y) {
            setSize(Vector2i(x, y));
        }
        virtual void setSize(Vector2i size) {
            this->transform.size.set(size);
            destRect = transform.ToRect();
        }

    public:
        int flag = -1;

    protected:
        Transform& parentTransform;
        SDL_Texture* spritesheet;
        SDL_Rect srcRect;
        SDL_Rect destRect;  
};

#endif
