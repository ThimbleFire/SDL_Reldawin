#ifndef _LPC_H_
#define _LPC_H_

#include "SceneObject.h"
#include "Vector2i.h"
#include "Camera.h"
#include "ResourceRepository.h"

class LocalPlayerCharacter : public SceneObject {
    public:
        LocalPlayerCharacter(const std::string& imagePath, Vector2i initialPosition) : Size(32, 48) {
            transform.position = initialPosition;    
            spriteTexture = g_resourceRepository.load(imagePath, renderer);
            if (spriteTexture == nullptr) {
                printf("Failed to load texture!\n");
            }            
        }
        ~LocalPlayerCharacter() = default;

        void Draw() const override {
            SDL_Rect destRect = { 
                transform.position.x,
                transform.position.y, 
                Size.x, 
                Size.y 
            };

            // Adjust position based on the camera
            destRect.x -= camera.getCameraRect().x;
            destRect.y -= camera.getCameraRect().y;

            // Render the sprite
            SDL_RenderCopy(renderer, spriteTexture, nullptr, &destRect);
        }

        void Update() override {
            // Implement your update logic here
        }

    private:
        const Vector2i Size;  // Size of the character (32x48 pixels)
        SDL_Texture* spriteTexture;
};

#endif
