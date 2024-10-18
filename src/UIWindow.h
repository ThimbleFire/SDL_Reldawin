#ifndef _UIWINDOW_H_
#define _UIWINDOW_H_

#include "SceneObject.h"
#include "ResourceRepository.h"
#include "UIElement.h"

/* UIWindow class is an image with a bunch of elements inside of it. These elements are best thought of as rectangles.
For example a draggable rectangle, a clickable rectangle, a mouseover rectangle.*/
class UIWindow : public SceneObject {
    public:
        UIWindow() {
            texture = g_resourceRepository.load("res/UI.png");
        }
        void Draw() const override {
            for (auto& obj : elements) {
                obj->Draw();
            }
        }
        void HandleInput(InputEvent& event) override {
            for (auto& obj : elements) {
                obj->HandleInput(event);
            }
        }

        void Update() override {
            for (auto& obj : elements) {
                obj->Update();
            }
        }

        void AddElement(UIElement* element) {
            element->setTexture(texture);
            elements.push_back(element);
        }
        void RemoveElement(int flag) {

        }

        void dispose() const override {
            for (auto& obj : elements) {
                obj->dispose();
                delete obj;
            }
            //element.clear();
        };

    public: 
        bool visible = false;

    private:
        SDL_Texture* texture;
        std::vector<UIElement*> elements;
};

#endif
