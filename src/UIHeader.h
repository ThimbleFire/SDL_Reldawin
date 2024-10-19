#ifndef _UIHEADER_H_
#define _UIHEADER_H_

#include "UIElement.h"
#include "UIResizeableTexture.h"
#include <string>

class UIHeader : public UIElement {

    public:
        UIHeader(std::string Name)
        {
            this->Name = Name;
            UIResizeableTexture* uiHeaderTexture = new UIResizeableTexture("UIHeaderTexture", { 242, 92, 24, 24 }, 1);
            uiHeaderTexture->transform.setAnchorPoints(0.0f, 0.0f, 1.0f, 0.0f);
            uiHeaderTexture->transform.setAnchorPixels(3, 3, 21, -15);
            uiHeaderTexture->setTexture(g_resourceRepository.load("res/UI.png"));
            uiHeaderTexture->SetHoverSrc({270, 92, 24, 24 });
            uiHeaderTexture->SetMouseDownSrc({214, 92, 24, 24 });
            this->addChild(uiHeaderTexture);
        }

        void Draw() const override {
            for (auto& obj : children) {
                obj->Draw();
            }
        }

        void HandleInput(InputEvent& event) override {
            UIElement::HandleInput(event);
        }
        void dispose() const override {
            UIElement::dispose();
        }
};

#endif