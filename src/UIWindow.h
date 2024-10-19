#ifndef _UIWINDOW_H_
#define _UIWINDOW_H_

#include "SceneObject.h"
#include "ResourceRepository.h"
#include "UIElement.h"

/* UIWindow class is an image with a bunch of elements inside of it. These elements are best thought of as rectangles.
For example a draggable rectangle, a clickable rectangle, a mouseover rectangle.*/
class UIWindow : public SceneObject {
    public:
        UIWindow(std::string Name) {
            this->Name = Name;
            texture = g_resourceRepository.load("res/UI.png");
        }
        void Draw() const override {
            if(!visible) return;
            for (auto& obj : children) {
                obj->Draw();
            }
        }
        void HandleInput(InputEvent& event) override {
            if(!visible) return;
            for (auto& obj : children) {
                obj->HandleInput(event);
            }
        }

        void Update() override {
            if(!visible) return;
            for (auto& obj : children) {
                obj->Update();
            }
        }

        void RemoveElement(int flag) {

        }

        void dispose() const override {
            for (auto& obj : children) {
                obj->dispose();
                delete obj;
            }
            //element.clear();
        };

    public: 
        bool visible = false;

    private:
        SDL_Texture* texture;
};

#endif
