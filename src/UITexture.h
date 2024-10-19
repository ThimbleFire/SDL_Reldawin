#ifndef _UITEXTURE_H_
#define _UITEXTURE_H_

#include "UIElement.h"

class UITexture : public UIElement {

    public:
        UITexture(std::string Name, SDL_Rect rect) : srcNormal(rect) {
            srcRect = srcNormal;
            this->Name = Name;
            Redraw();

            onMouseEnter.subscribe([this]() { onHoverStart(); });
            onMouseLeave.subscribe([this]() { onHoverEnd(); });
            onMouseDown.subscribe([this]() { onMousePressed(); });
            onMouseUp.subscribe([this]() { onMouseReleased(); });
        }

        void Draw() const override {
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &srcRect, &destRect);

            for (auto& obj : children) {
                obj->Draw();
            }
        }

        void SetHoverSrc(SDL_Rect hover) {
            this->srcHover = hover;
            has_hover = true;
        }

        void SetMouseDownSrc(SDL_Rect down) {
            this->srcPressed = down;
            has_down = true;
        }

        void onHoverStart() {
            if (has_hover) {
                srcRect = srcHover;
            }
        }

        void onHoverEnd() {
            if (has_hover) {
                srcRect = srcNormal;
            }
        }

        void onMousePressed() {
            if (has_down) {
                srcRect = srcPressed;
            }
        }

        void onMouseReleased() {
            if (has_down && has_hover) {
                srcRect = srcHover;
            }
        }

    private:
        SDL_Rect srcNormal;
        SDL_Rect srcHover;
        SDL_Rect srcPressed;

        bool has_hover = false;
        bool has_down = false;

};

#endif