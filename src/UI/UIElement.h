#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

#include "SceneObject.h"
#include "ResourceRepository.h"

class UIElement : public SceneObject {
    public:
        UIElement() {
        spritesheet = g_resourceRepository.load("res/UI.png");
        }
        ~UIElement();

        void Draw() const override {
            
        }

        void HandleInput() const override {
            
        }

        void dispose() const override {
            
        }

    public:
        int flag = -1;

    protected:
        Vector2i Size;
        Transform* parentTransform;
        SDL_Texture* spritesheet;
};

#endif
