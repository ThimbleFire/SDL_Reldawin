#ifndef _TESTWINDOW_H_
#define _TESTWINDOW_H_

#include "SceneObject.h"
#include "UI.h"
#include <random>

class TestWindow : public SceneObject {
    public:
        TestWindow()
        {
            transform.size.set(300, 350);

            UIResizeableTexture* uiBackground = new UIResizeableTexture("UIBody", { 186, 92, 24, 24 }, 1);
            uiBackground->setTexture(g_resourceRepository.load("res/UI.png"));
            addChild(uiBackground);

            UIResizeableTexture* uiHeaderTexture = new UIResizeableTexture("UIHeaderTexture", { 242, 92, 24, 24 }, 1);
            uiHeaderTexture->transform.setAnchorPoints(0.0f, 0.0f, 1.0f, 0.0f);
            uiHeaderTexture->transform.setAnchorPixels(3, 3, 21, -15);
            uiHeaderTexture->setTexture(g_resourceRepository.load("res/UI.png"));
            uiHeaderTexture->SetHoverSrc({270, 92, 24, 24 });
            uiHeaderTexture->SetMouseDownSrc({214, 92, 24, 24 });
            addChild(uiHeaderTexture);

            UITexture* uiButtonBackgroundTest = new UITexture("btnBackground", { 44, 44, 12, 12 });
            uiButtonBackgroundTest->transform.setAnchorPoints(1.0f, 0.0f, 1.0f, 0.0f);
            uiButtonBackgroundTest->transform.setAnchorPixels( -17, 3, 5, -15 );
            uiButtonBackgroundTest->setTexture(g_resourceRepository.load("res/UI.png"));
            uiButtonBackgroundTest->SetHoverSrc({30, 44, 12, 12 });
            uiButtonBackgroundTest->SetMouseDownSrc({ 582, 427, 12, 12 });
            addChild(uiButtonBackgroundTest);

            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                std::cerr << (*it)->Name << std::endl;
            }

            uiButtonBackgroundTest->onMouseDown.subscribe([this]() { 
               visible = !visible; 
            });
            uiHeaderTexture->onDrag.subscribe([this](int x, int y) {
                // it's unclear why but, yeah.
               transform.SetPosition(x/2, y/2);
            });
        }

        void HandleInput(InputEvent& event) override {
            // iterate backwards so the top-most UI elements are handled first
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                (*it)->HandleInput(event);
            }
            if(event.event.type == SDL_KEYDOWN)
            {
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if(state[SDL_SCANCODE_E])
                {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(50, 500);
                    transform.SetSize(dis(gen), dis(gen));
                    return;
                }
                Vector2i inputVector(
                    state[SDL_SCANCODE_A] ? -1 : state[SDL_SCANCODE_D] ? 1 : 0,
                    state[SDL_SCANCODE_S] ? 1 : state[SDL_SCANCODE_W] ? -1 : 0 
                );
                transform.Translate(inputVector * 10);
                if (state[SDL_SCANCODE_I]) {
                    visible = ! visible;
                }
            }
        }

        void Draw() const override {
            for (auto& obj : children) {
                if(visible == false) return;
                obj->Draw();
            }
        }

};

#endif