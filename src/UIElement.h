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


        bool mouseDownOverElement = false;
        SDL_Point previousMousePos = {0, 0};  // Store the previous mouse position

        void HandleInput(InputEvent& event) override
        {
            if(event.handled) return;

            SDL_Point point = { event.screen.x, event.screen.y };

            // Check if the mouse is over the element
            if (SDL_PointInRect(&point, &destRect)) {
                // Fire onMouseEnter if not already moused over
                if (!isMousedOver) {
                    event.handled = true;
                    isMousedOver = true;
                    onMouseEnter.invoke();
                    std::cerr << ToString() + ":onMouseEnter" << std::endl;
                }

                // Check for mouse button down and fire onMouseDown
                if(event.event.type == SDL_MOUSEBUTTONDOWN) {
                    event.handled = true;
                    onMouseDown.invoke();
                    mouseDownOverElement = true;  // Track that the mouse is pressed over this element
                    previousMousePos = point;  // Initialize the drag tracking
                    std::cerr << ToString() + ":onMouseDown" << std::endl;
                    return;
                }
            } 
            else {
                // Fire onMouseLeave if not holding the mouse button down
                if (isMousedOver && !mouseDownOverElement) {
                    event.handled = true;
                    isMousedOver = false;
                    onMouseLeave.invoke();
                    std::cerr << ToString() + ":onMouseExit" << std::endl;
                }
            }

            // Handle dragging: mouse is down, and we are receiving mouse motion events
            if (mouseDownOverElement && event.event.type == SDL_MOUSEMOTION) {
                event.handled = true;
                SDL_Point delta = {
                    point.x - previousMousePos.x,  // Calculate movement delta
                    point.y - previousMousePos.y
                };
                previousMousePos = point;  // Update the previous position

                onDrag.invoke(delta.x, delta.y);  // Fire the onDrag event with movement delta
                return;
            }

            // Handle mouse button release
            if (mouseDownOverElement && event.event.type == SDL_MOUSEBUTTONUP) {
                event.handled = true;
                onMouseUp.invoke();
                mouseDownOverElement = false;  // Reset the mouse button state on release
                std::cerr << ToString() + ":onMouseUp" << std::endl;
                return;
            }

            // Handle children last
            for (auto& obj : children) {
                obj->HandleInput(event);
                if (event.handled) break;
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
