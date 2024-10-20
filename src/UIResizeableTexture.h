#ifndef _UIBODY_H_
#define _UIBODY_H_

#include "UIElement.h"

class UIResizeableTexture : public UIElement {

    public:
        UIResizeableTexture(std::string Name, SDL_Rect rect, int edgeBorder)
            : edgeBorder(edgeBorder), normal(rect) {
            srcRect = normal;
            this->Name = Name;
            CalculateSrc();
            Redraw();
            
            onMouseEnter.subscribe([this]() { onHoverStart(); });
            onMouseLeave.subscribe([this]() { onHoverEnd(); });
            onMouseDown.subscribe([this]() { onMousePressed(); });
            onMouseUp.subscribe([this]() { onMouseReleased(); });
        }
        
        void Draw() const override {
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_top_left, &dest_top_left);
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_top, &dest_top);
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_top_right, &dest_top_right);
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_left, &dest_left);
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_mid, &dest_mid);
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_right, &dest_right);
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_bot_left, &dest_bot_left);
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_bot, &dest_bot);
            SDL_RenderCopy(g_resourceRepository.renderer, spritesheet, &src_bot_right, &dest_bot_right);

            for (auto& obj : children) {
                obj->Draw();
            }
        }
        
        void Redraw() override {            
            dest_top_left   = calcDestRect(0, 0, edgeBorder, edgeBorder);
            dest_top        = calcDestRect(edgeBorder, 0, transform.size.x - edgeBorder * 2, edgeBorder);
            dest_top_right  = calcDestRect(transform.size.x - edgeBorder, 0, edgeBorder, edgeBorder);
            dest_left       = calcDestRect(0, edgeBorder, edgeBorder, transform.size.y - edgeBorder * 2);
            dest_mid        = calcDestRect(edgeBorder, edgeBorder, transform.size.x - edgeBorder * 2, transform.size.y - edgeBorder * 2);
            dest_right      = calcDestRect(transform.size.x - edgeBorder, edgeBorder, edgeBorder, transform.size.y - edgeBorder * 2);
            dest_bot_left   = calcDestRect(0, transform.size.y - edgeBorder, edgeBorder, edgeBorder);
            dest_bot        = calcDestRect(edgeBorder, transform.size.y - edgeBorder, transform.size.x - edgeBorder * 2, edgeBorder);
            dest_bot_right  = calcDestRect(transform.size.x - edgeBorder, transform.size.y - edgeBorder, edgeBorder, edgeBorder);
        
            UIElement::Redraw();
        }

        void SetHoverSrc(SDL_Rect hover) {
            this->hover = hover;
            has_hover = true;
        }

        void SetMouseDownSrc(SDL_Rect down) {
            this->mouse_down = down;
            has_down = true;
        }

        void onHoverStart() {
            if (has_hover) {
                srcRect = hover;
                CalculateSrc();
            }
        }

        void onHoverEnd() {
            if (has_hover) {
                srcRect = normal;
                CalculateSrc();
            }
        }

        void onMousePressed() {
            if (has_down) {
                srcRect = mouse_down;
                CalculateSrc();
            }
        }

        void onMouseReleased() {
            if (has_down && has_hover) {
                srcRect = hover;  // Reset to hover on mouse up
                CalculateSrc();
            }
        }


    private:
        void CalculateSrc() {
            src_top_left =  { srcRect.x, srcRect.y, edgeBorder, edgeBorder };
            src_top =       { srcRect.x + edgeBorder, srcRect.y, srcRect.w - edgeBorder * 2, edgeBorder };
            src_top_right = { srcRect.x + srcRect.w - edgeBorder, srcRect.y, edgeBorder, edgeBorder };
            src_left =      { srcRect.x, srcRect.y + edgeBorder, edgeBorder, srcRect.h - edgeBorder * 2 };
            src_mid =       { srcRect.x + edgeBorder, srcRect.y + edgeBorder, srcRect.w - edgeBorder * 2, srcRect.h - edgeBorder * 2 };
            src_right =     { srcRect.x + srcRect.w - edgeBorder, srcRect.y + edgeBorder, edgeBorder, srcRect.h - edgeBorder * 2 };
            src_bot_left =  { srcRect.x, srcRect.y + srcRect.h - edgeBorder, edgeBorder, edgeBorder };
            src_bot =       { srcRect.x + edgeBorder, srcRect.y + srcRect.h - edgeBorder, srcRect.w - edgeBorder * 2, edgeBorder };
            src_bot_right = { srcRect.x + srcRect.w - edgeBorder, srcRect.y + srcRect.h - edgeBorder, edgeBorder, edgeBorder };  
        }

    private:
        int edgeBorder = 0;

        SDL_Rect normal;
        SDL_Rect hover;
        SDL_Rect mouse_down;

        bool has_hover = false;
        bool has_down = false;

        SDL_Rect src_top_left, src_top, src_top_right;
        SDL_Rect src_left, src_mid, src_right;
        SDL_Rect src_bot_left, src_bot, src_bot_right;
        SDL_Rect dest_top_left, dest_top, dest_top_right;
        SDL_Rect dest_left, dest_mid, dest_right;
        SDL_Rect dest_bot_left, dest_bot, dest_bot_right;
};

#endif
