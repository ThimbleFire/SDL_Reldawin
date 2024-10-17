#ifndef _UIWINDOW_H_
#define _UIWINDOW_H_

#include "SceneObject.h"
#include "ResourceRepository.h"

/* UIWindow class is a dynamic, reusable interface that can have UI elements added to it. 
UIElements are anchored to it and are rendered over it.*/
class UIWindow : SceneObject {
    public:
        UIWindow(int x, int y, int w) : Size(w, 0) { }
        ~UIWindow();

        void Draw() const override;
        void HandleInput() const override;

        void dispose() const override;
    private:
        Vector2i Size;
};

#endif
