#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <vector>
#include "Base.h"
#include "Vector2i.h"
#include "Vector2.h"
#include <SDL2/SDL_rect.h>
#include <functional>

class Transform : public Base {
    public:
        void SetPosition(int x, int y);
        void SetPosition(Vector2i newPosition);
        void SetSize(int width, int height);
        void SetSize(Vector2i newSize);
        void Translate(int x, int y);
        void Translate(Vector2i position);
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

        void SubscribeToPositionChange(const std::function<void()>& callback);
        void SubscribeToSizeChange(const std::function<void()>& callback);

        // Utility functions
        std::string ToString() const override;
        SDL_Rect ToRect();

    public:
        Vector2i position;
        Vector2i size;
        bool resizeWithParent = true;

    private:
        std::vector<std::function<void()>> positionChangeSubscribers;
        std::vector<std::function<void()>> sizeChangeSubscribers;
        
        void NotifyPositionChanged();
        void NotifySizeChanged();

    private:
        float left = 0.0f, top = 0.0f, right = 1.0f, bottom = 1.0f;
        int pixel_left = 0, pixel_top = 0, pixel_right = 0, pixel_bottom = 0;
};

#endif
