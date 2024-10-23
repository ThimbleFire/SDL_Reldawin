#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "SceneObject.h"
#include "ResourceRepository.h"

class Cursor : public SceneObject {

    SDL_Texture* texture;

    public:
        Cursor(const std::string& path) {
            texture = g_resourceRepository.load(path);
            transform.size.set(64, 32);
        }

        void HandleInput(InputEvent& event) override {
            transform.position.set(Math::CellToWorld(event.cell));            
        }

        void Draw() const override {
            SDL_FRect destRect = transform.ToRect();

            // Adjust position based on the camera
            destRect.x -= camera.ToRect().x;
            destRect.y -= camera.ToRect().y;

            // Render the sprite
            SDL_RenderCopyF(g_resourceRepository.renderer, texture, nullptr, &destRect);
        }

};

#endif