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

        // Elements are given a flag which is used to identify them in the event of needing to be removed from the window
        void AddElement(UIElement* element);
        void RemoveElement(int flag);

        void dispose() const override;

    public: 
        bool visible = false;

    private:
        Vector2i Size;
        std::vector<UIElement*> element;
};

#endif
