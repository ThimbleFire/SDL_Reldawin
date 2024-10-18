#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

#include "SceneObject.h"
#include "ResourceRepository.h"

class UIElement : public SceneObject {
    public:
        UIElement();
        ~UIElement();

        void Draw() const override {
            
        }

        void HandleInput() const override {
            
        }

        void dispose() const override {
            
        }

    public:
        int flag = -1;

    private:
        Vector2i Size;
        Transform* parentTransform;
};

#endif
