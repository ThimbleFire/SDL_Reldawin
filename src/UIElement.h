#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

#include "SceneObject.h"
#include "ResourceRepository.h"
#include "Event.h"
#include <string>

class UIElement : public SceneObject {

    public:
        Event onMouseDown;
        Event onMouseUp;
        Event onMouseEnter;
        Event onMouseLeave;

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
                    onMouseDown.invoke(); 
                    return;
                }
                else if(event.event.type == SDL_MOUSEBUTTONUP) {
                    event.handled = true;
                    onMouseUp.invoke();
                    return;
                }
            }
            
            SDL_Point point = { event.screen.x, event.screen.y };
            if (SDL_PointInRect(&point, &destRect)) {
                if (!isMousedOver) {
                    isMousedOver = true;
                    onMouseEnter.invoke();
                }
            } 
            else {
                if (isMousedOver) {
                    isMousedOver = false;
                    onMouseLeave.invoke();
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

        void Redraw() override {
            destRect = calcDestRect(0, 0, transform.size.x, transform.size.y);
        }

    protected:
        SDL_Rect calcDestRect(int x_offset, int y_offset, int width, int height) {
            if(parent != nullptr)
            {
                return {
                    transform.position.x + parent->transform.position.x + x_offset,
                    transform.position.y + parent->transform.position.y + y_offset,
                    width, 
                    height
                };
            }
            else
            {
                return {
                    transform.position.x + x_offset,
                    transform.position.y + y_offset,
                    width,
                    height
                };
            }
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
