#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include <iostream>
#include "Transform.h"
#include "InputEvent.h"

class SceneObject : public Base {

    public:
        virtual void Draw() const = 0;
        virtual void Update() {}
        virtual void HandleInput(InputEvent& event) {}   
        // Redraw instructs the inheriting object to recalculate destRect
        virtual void Redraw() {}   
        virtual void dispose() const = 0;

        std::string ToString() const override {
            return Name;
        }

        void removeParent() {
            parent = nullptr;
        }

        void addChild(SceneObject* child) {
            child->parent = this;
            children.push_back(child);
            
            this->transform.SubscribeToPositionChange([child, this]() {
                printf("child moved to reflect parent position change\n");
                child->transform.UpdateInAccordanceWithParent(this->transform);
                child->Redraw();
            });
            this->transform.SubscribeToSizeChange([child, this]() {
                child->transform.UpdateInAccordanceWithParent(this->transform);
                printf("child resized to reflect parent size change\n");
                child->Redraw();
            });

            child->transform.UpdateInAccordanceWithParent(this->transform);
            child->Redraw();
        }

        virtual ~SceneObject() {
            for (SceneObject* child : children) {
                delete child;  // Assuming ownership of children
            }
            children.clear();  // Clean the vector to avoid dangling pointers
        }

    public:
        Transform transform;
        SceneObject* parent = nullptr;
        std::vector<SceneObject*> children;
};


#endif
