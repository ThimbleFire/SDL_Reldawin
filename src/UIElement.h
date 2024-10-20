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
        EventTurple onDrag;  // Define the onDrag event

    public:
        void Draw() const override {
            for (auto& obj : children) {
                obj->Draw();
            }
        }

        void HandleInput(InputEvent& event) override {
            if(event.handled) return;

            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                (*it)->HandleInput(event);
                if (event.handled) 
                    break;
            }

            SDL_Point point = { event.screen.x, event.screen.y };

            // Check if mouse is over the element
            if (SDL_PointInRect(&point, &destRect))
            {
                if (!isMousedOver)
                {
                    event.handled = doesHoverHandleEvent;
                    isMousedOver = true;
                    onMouseEnter.invoke();
                    return;
                }
                // Mouse button down
                if (event.event.type == SDL_MOUSEBUTTONDOWN)
                {
                    event.handled = doesClickHandleEvent;
                    onMouseDown.invoke();
                    mouseDownOverElement = true;
                    offset = event.screen - (parent->transform.position*2);
                    return;
                }
            }
            else
            {
                if (isMousedOver && !mouseDownOverElement)
                {
                    event.handled = doesHoverHandleEvent;
                    isMousedOver = false;
                    onMouseLeave.invoke();
                    return;
                }
            }

            // Mouse button up
            if (mouseDownOverElement && event.event.type == SDL_MOUSEBUTTONUP) {
                event.handled = doesClickHandleEvent;
                onMouseUp.invoke();
                mouseDownOverElement = false;
                return;
            }

            // Drag behavior
            if (mouseDownOverElement && event.event.type == SDL_MOUSEMOTION)
            {
                event.handled = doesDragHandleEvent;
                Vector2i newPosition = event.screen - offset;
                onDrag.invoke(newPosition.x, newPosition.y);
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
        bool doesHoverHandleEvent = false;
        bool doesClickHandleEvent = true;
        bool doesDragHandleEvent = false;

    protected:
        SDL_Texture* spritesheet;
        SDL_Rect srcRect;
        SDL_Rect destRect;

    private:
        bool isMousedOver = false;
        bool mouseDownOverElement = false;
        Vector2i offset; 
};

#endif
