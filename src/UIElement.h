#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

#include "SceneObject.h"
#include "ResourceRepository.h"

class UIElement : public SceneObject {

    public:
        void Draw() const override {
            for (auto& obj : children) {
                obj->Draw();
            }
        }
        void HandleInput(InputEvent& event) override
        {
            for (auto& obj : children) {
                obj->HandleInput(event);
            }
        }
        void dispose() const override
        {
            for (auto& obj : children) {
                obj->dispose();
            }
        }
        void setTexture(SDL_Texture* texture) {
            spritesheet = texture;
        }

    public:
        int flag = -1;

    protected:
        SDL_Texture* spritesheet;
        SDL_Rect srcRect;
        SDL_Rect destRect;
};

#endif
