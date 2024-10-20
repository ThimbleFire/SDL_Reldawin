#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include <iostream>
#include <string>
#include "Transform.h"
#include "InputEvent.h"

class SceneObject : public Base {

    public:
        virtual ~SceneObject() {
            for (SceneObject* child : children) {
                delete child;  // Assuming ownership of children
            }
            children.clear();  // Clean the vector to avoid dangling pointers
        }
        virtual void Draw() const = 0;
        virtual void Update() {}
        virtual void HandleInput(InputEvent& event) {}   
        virtual void Redraw() {}
        virtual void dispose() const {};

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
                child->transform.UpdateInAccordanceWithParent(this->transform);
                child->Redraw();
            });
            this->transform.SubscribeToSizeChange([child, this]() {
                child->transform.UpdateInAccordanceWithParent(this->transform);
                child->Redraw();
            });

            child->transform.UpdateInAccordanceWithParent(this->transform);

            for (SceneObject* child : children) {
                child->Redraw();
            }
        }
        SceneObject* get_child(int i) {
            return children.at(i);
        }

    public:
        Transform transform;
        SceneObject* parent = nullptr;
        bool visible = true;

    protected:
        std::vector<SceneObject*> children;
};


#endif
