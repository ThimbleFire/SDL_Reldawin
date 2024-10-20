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
        EventTurple onDrag; 

    public:
        void Draw() const override {
            for (auto& obj : children) {
                obj->Draw();
            }
        }

        bool isMousedOver = false;
        bool mouseDownOverElement = false;
        Vector2i offset;

        void HandleInput(InputEvent& event) override {
            if(event.handled) return;            

            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                (*it)->HandleInput(event);
                if (event.handled) 
                    break;
            }

            SDL_Point point = { event.screen.x, event.screen.y };

            if (SDL_PointInRect(&point, &destRect)) {
                if (!isMousedOver) {
                    event.handled = true;
                    isMousedOver = true;
                    onMouseEnter.invoke();
                }

                if (event.event.type == SDL_MOUSEBUTTONDOWN) {
                    event.handled = true;
                    onMouseDown.invoke();
                    mouseDownOverElement = true;

                    offset = event.screen - transform.position;
                    return;
                }
            } else {
                if (isMousedOver && !mouseDownOverElement) {
                    event.handled = true;
                    isMousedOver = false;
                    onMouseLeave.invoke();
                }
            }

            if (mouseDownOverElement && event.event.type == SDL_MOUSEMOTION) {
                event.handled = true;

                Vector2i newPosition = event.screen - offset;

                onDrag.invoke(newPosition.x, newPosition.y);
                return;
            }

            if (mouseDownOverElement && event.event.type == SDL_MOUSEBUTTONUP) {
                event.handled = true;
                onMouseUp.invoke();
                mouseDownOverElement = false;
                return;
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

    protected:
        SDL_Texture* spritesheet;
        SDL_Rect srcRect;
        SDL_Rect destRect;
};

#endif
