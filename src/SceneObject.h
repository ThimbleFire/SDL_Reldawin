#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "Transform.h"
#include "InputEvent.h"

class SceneObject : public Base {
    public:
        virtual void Draw() const = 0;
        virtual void Update() {}
        virtual void HandleInput(InputEvent& event) {}
        
        virtual void dispose() const = 0;

        std::string ToString() const override {
            return Name;
        }
public:
        Transform transform;
};

#endif
