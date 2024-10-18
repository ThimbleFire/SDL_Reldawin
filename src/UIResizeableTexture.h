#ifndef _UIBODY_H_
#define _UIBODY_H_

#include "UIElement.h"

class UIResizeableTexture : public UIElement {

    public:
        enum LayoutMode { POSITION, ANCHOR };

    public:
        UIResizeableTexture(Transform& parentTransform, SDL_Rect rect, int edgeBorder, LayoutMode layoutMode) 
            : UIElement(parentTransform), edgeBorder(edgeBorder), layoutMode(layoutMode) {
            
            src_top_left =  { rect.x, rect.y, edgeBorder, edgeBorder };
            src_top =       { rect.x + edgeBorder, rect.y, rect.w - edgeBorder * 2, edgeBorder };
            src_top_right = { rect.x + rect.w - edgeBorder, rect.y, edgeBorder, edgeBorder };
            src_left =      { rect.x, rect.y + edgeBorder, edgeBorder, rect.h - edgeBorder * 2 };
            src_mid =       { rect.x + edgeBorder, rect.y + edgeBorder, rect.w - edgeBorder * 2, rect.h - edgeBorder * 2 };
            src_right =     { rect.x + rect.w - edgeBorder, rect.y + edgeBorder, edgeBorder, rect.h - edgeBorder * 2 };
            src_bot_left =  { rect.x, rect.y + rect.h - edgeBorder, edgeBorder, edgeBorder };
            src_bot =       { rect.x + edgeBorder, rect.y + rect.h - edgeBorder, rect.w - edgeBorder * 2, edgeBorder };
            src_bot_right = { rect.x + rect.w - edgeBorder, rect.y + rect.h - edgeBorder, edgeBorder, edgeBorder };

            parentTransform.SubscribeToSizeChange([this](const Vector2i& newSize) {
                this->setSize(newSize);
                this->redraw();
                if(this->layoutMode == LayoutMode::ANCHOR) {
                    setAnchorPoints(left, top, right, bottom, pixel_left, pixel_top, pixel_right, pixel_bottom);
                }
            });
            parentTransform.SubscribeToPositionChange([this](const Vector2i& newPosition) {
                this->redraw();
            });
            
        }

        void redraw() {
            dest_top_left   = calcDestRect(0, 0, edgeBorder, edgeBorder);
            dest_top        = calcDestRect(edgeBorder, 0, transform.size.x - edgeBorder * 2, edgeBorder);
            dest_top_right  = calcDestRect(transform.size.x - edgeBorder, 0, edgeBorder, edgeBorder);
            dest_left       = calcDestRect(0, edgeBorder, edgeBorder, transform.size.y - edgeBorder * 2);
            dest_mid        = calcDestRect(edgeBorder, edgeBorder, transform.size.x - edgeBorder * 2, transform.size.y - edgeBorder * 2);
            dest_right      = calcDestRect(transform.size.x - edgeBorder, edgeBorder, edgeBorder, transform.size.y - edgeBorder * 2);
            dest_bot_left   = calcDestRect(0, transform.size.y - edgeBorder, edgeBorder, edgeBorder);
            dest_bot        = calcDestRect(edgeBorder, transform.size.y - edgeBorder, transform.size.x - edgeBorder * 2, edgeBorder);
            dest_bot_right  = calcDestRect(transform.size.x - edgeBorder, transform.size.y - edgeBorder, edgeBorder, edgeBorder);
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
        }

        void HandleInput(InputEvent& event) override {
            if(event.handled) return;
            SDL_Point point = { event.screen.x, event.screen.y };
            if (SDL_PointInRect(&point, &dest_mid)) {
                event.handled = true;
            }
        }

        void setSize(int x, int y) override {
            setSize(Vector2i(x, y));
        }

        void setSize(Vector2i size) override {
            this->transform.size.set(size);
            destRect = transform.ToRect();
            this->redraw();
        }

        void setLayoutMode(LayoutMode mode) {
            this->layoutMode = mode;
        }

        void setAnchorPoints(float left, float top, float right, float bottom, int pixel_left, int pixel_top, int pixel_right, int pixel_bottom) {
            transform.position.set(
                static_cast<int>(parentTransform.position.x + left * parentTransform.size.x) + pixel_left,
                static_cast<int>(parentTransform.position.y + top * parentTransform.size.y) + pixel_top
            );
            
            transform.size.set(
                static_cast<int>((right - left) * parentTransform.size.x) - (pixel_left + pixel_right),
                static_cast<int>((bottom - top) * parentTransform.size.y) - (pixel_top - pixel_bottom)
            );
            
            setSize(transform.size);
            redraw();

            this->left = left;
            this->top = top;
            this->bottom = bottom;
            this->right = right;
            this->pixel_left = pixel_left;
            this->pixel_top = pixel_top;
            this->pixel_right = pixel_right;
            this->pixel_bottom = pixel_bottom;
        }

    private:
        float left = 0.0f, top = 0.0f, right = 0.0f, bottom = 0.0f;
        int pixel_left = 0, pixel_top = 0, pixel_right = 0, pixel_bottom = 0;
        int edgeBorder = 0;
        LayoutMode layoutMode = LayoutMode::POSITION;
        SDL_Rect src_top_left, src_top, src_top_right;
        SDL_Rect src_left, src_mid, src_right;
        SDL_Rect src_bot_left, src_bot, src_bot_right;
        SDL_Rect dest_top_left, dest_top, dest_top_right;
        SDL_Rect dest_left, dest_mid, dest_right;
        SDL_Rect dest_bot_left, dest_bot, dest_bot_right;

    private:
        SDL_Rect calcDestRect(int x_offset, int y_offset, int width, int height) {
            return {
                transform.position.x + parentTransform.position.x + x_offset,
                transform.position.y + parentTransform.position.y + y_offset,
                width, height
            };
        }
};

#endif
