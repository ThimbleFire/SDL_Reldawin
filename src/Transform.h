#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <vector>
#include "Base.h"
#include "Vector2i.h"
#include "Vector2.h"
#include <SDL2/SDL_rect.h>
#include <functional>
#include "Event.h"

class Transform : public Base {
    public:
        Event onPositionChanged;
        Event onSizeChanged;

    public:
        void SetPosition(float x, float y);
        void SetPosition(Vector2 newPosition);
        
        void SetSize(float width, float height);
        void SetSize(Vector2 newSize);

        void Translate(float x, float y);
        void Translate(Vector2 position);

        void setAnchorPoints(float left, float top, float right, float bottom) {
            this->left = left;
            this->top = top;
            this->bottom = bottom;
            this->right = right;
        }
        void setAnchorPixels(int pixel_left, int pixel_top, int pixel_right, int pixel_bottom) {
            this->pixel_left = pixel_left;
            this->pixel_top = pixel_top;
            this->pixel_right = pixel_right;
            this->pixel_bottom = pixel_bottom;
        }
        void UpdateInAccordanceWithParent(Transform& parent);

        // Utility functions
        std::string ToString() const override;
        SDL_FRect ToRect() const;

    public:
        Vector2 position;
        Vector2 size;
        bool resizeWithParent = true;

    private:
        float left = 0.0f, top = 0.0f, right = 1.0f, bottom = 1.0f;
        int pixel_left = 0, pixel_top = 0, pixel_right = 0, pixel_bottom = 0;
};

#endif
