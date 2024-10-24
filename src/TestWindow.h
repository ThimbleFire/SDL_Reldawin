#ifndef _TESTWINDOW_H_
#define _TESTWINDOW_H_

#include "Engine/SceneObject.h"
#include "Engine/UI.h"
#include <random>

class TestWindow : public SceneObject {
    public:
        TestWindow()
        {
            transform.size.set(150, 250);

            UIResizeableTexture* uiBackground = new UIResizeableTexture("UIBody", { 186, 92, 24, 24 }, 1);
            uiBackground->setTexture(g_resourceRepository.load("res/UI.png"));
            uiBackground->doesHoverHandleEvent = true;
            addChild(uiBackground);

            UIResizeableTexture* uiHeaderTexture = new UIResizeableTexture("UIHeaderTexture", { 242, 92, 24, 24 }, 1);
            uiHeaderTexture->transform.setAnchorPoints(0.0f, 0.0f, 1.0f, 0.0f);
            uiHeaderTexture->transform.setAnchorPixels(3, 3, 21, -15);
            uiHeaderTexture->setTexture(g_resourceRepository.load("res/UI.png"));
            uiHeaderTexture->SetHoverSrc({270, 92, 24, 24 });
            uiHeaderTexture->SetMouseDownSrc({214, 92, 24, 24 });
            uiHeaderTexture->doesDragHandleEvent = true;
            addChild(uiHeaderTexture);

            UITexture* uiButtonBackgroundTest = new UITexture("btnBackground", { 44, 44, 12, 12 });
            uiButtonBackgroundTest->transform.setAnchorPoints(1.0f, 0.0f, 1.0f, 0.0f);
            uiButtonBackgroundTest->transform.setAnchorPixels( -17, 3, 5, -15 );
            uiButtonBackgroundTest->setTexture(g_resourceRepository.load("res/UI.png"));
            uiButtonBackgroundTest->SetHoverSrc({30, 44, 12, 12 });
            uiButtonBackgroundTest->SetMouseDownSrc({ 582, 427, 12, 12 });
            uiButtonBackgroundTest->doesDragHandleEvent = true;
            addChild(uiButtonBackgroundTest);

            UILabel* uiLabel = new UILabel("Debugger", "res/PIXEAB__.TTF");
            uiLabel->transform.setAnchorPoints(0.5f, 0.0f, 0.0f, 0.0f);
            uiLabel->transform.setAnchorPixels(-30, 2, 0, 0);
            uiLabel->doesClickHandleEvent = false;
            addChild(uiLabel);

            UILabel* uiFramerate = new UILabel("FPS {0}", "res/PIXEAB__.TTF");
            uiFramerate->transform.setAnchorPoints(0.0f, 0.0f, 0.0f, 0.0f);
            uiFramerate->transform.setAnchorPixels(5, 16, 0, 0);
            uiFramerate->doesClickHandleEvent = false;
            addChild(uiFramerate);

            UILabel* uiLPCPosition = new UILabel("LPC Position: {0}", "res/PIXEAB__.TTF");
            uiLPCPosition->transform.setAnchorPoints(0.0f, 0.0f, 0.0f, 0.0f);
            uiLPCPosition->transform.setAnchorPixels(5, 30, 0, 0);
            uiLPCPosition->doesClickHandleEvent = false;
            addChild(uiLPCPosition);

            UILabel* uiLPCCell = new UILabel("LPC Cell: {0}", "res/PIXEAB__.TTF");
            uiLPCCell->transform.setAnchorPoints(0.0f, 0.0f, 0.0f, 0.0f);
            uiLPCCell->transform.setAnchorPixels(5, 44, 0, 0);
            uiLPCCell->doesClickHandleEvent = false;
            addChild(uiLPCCell);

            UILabel* uiCursorOverCell = new UILabel("Cursor over cell: {0}", "res/PIXEAB__.TTF");
            uiCursorOverCell->transform.setAnchorPoints(0.0f, 0.0f, 0.0f, 0.0f);
            uiCursorOverCell->transform.setAnchorPixels(5, 58, 0, 0);
            uiCursorOverCell->doesClickHandleEvent = false;
            addChild(uiCursorOverCell);

            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                std::cerr << (*it)->Name << std::endl;
            }

            uiButtonBackgroundTest->onMouseUp.subscribe([this]() { 
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