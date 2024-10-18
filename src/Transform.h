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

        // Methods to translate the position
        void Translate(int x, int y);
        void Translate(Vector2i position);
        void Translate(Vector2 position);

        void SubscribeToPositionChange(const std::function<void(const Vector2i&)>& callback);
        void SubscribeToSizeChange(const std::function<void(const Vector2i&)>& callback);

        // Utility functions
        std::string ToString() const override;
        SDL_Rect ToRect();

    public:
        Vector2i position;
        Vector2i size;

    private:
        std::vector<std::function<void(const Vector2i&)>> positionChangeSubscribers;
        std::vector<std::function<void(const Vector2i&)>> sizeChangeSubscribers;
        
        void NotifyPositionChanged();
        void NotifySizeChanged();
};

#endif
