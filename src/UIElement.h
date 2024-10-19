#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

#include "SceneObject.h"
#include "ResourceRepository.h"
#include <string>

class UIElement : public SceneObject {

    virtual void onHoverStart() { 
        std::cerr << "hover start" << std::endl;
    }
    virtual void onHoverEnd() { 
        std::cerr << "hover end" << std::endl;
    }
    virtual void onMouseDown() { 
        std::cerr << "lmb down" << std::endl;
    }
    virtual void onMouseUp() { 
        std::cerr << "lmb up" << std::endl;
    }

    public:
        void Draw() const override {
            for (auto& obj : children) {
                obj->Draw();
            }
        }
        void HandleInput(InputEvent& event) override
        {
            if(event.handled) return;

            for (auto& obj : children) {
                obj->HandleInput(event);
                if (event.handled) break;
            }
            
            if (isMousedOver)
            {
                if(event.event.type == SDL_MOUSEBUTTONDOWN) {
                    event.handled = true;
                    onMouseDown(); 
                    return;
                }
                else if(event.event.type == SDL_MOUSEBUTTONUP) {
                    onMouseUp();
                    event.handled = true;
                    return;
                }
            }
            
            SDL_Point point = { event.screen.x, event.screen.y };
            if (SDL_PointInRect(&point, &destRect)) {
                if (!isMousedOver) {
                    isMousedOver = true;
                    onHoverStart();
                }
            } 
            else {
                if (isMousedOver) {
                    isMousedOver = false;
                    onHoverEnd();
                }
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
        bool isMousedOver = false;

    protected:
        SDL_Texture* spritesheet;
        SDL_Rect srcRect;
        SDL_Rect destRect;
};

#endif
