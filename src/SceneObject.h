#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "Transform.h"

class SceneObject : public Base {
    public:
        virtual void Draw() const = 0;
        virtual void Update() {}

        std::string ToString() const override {
            return Name;
        }
public:
        Transform transform;
};

#endif