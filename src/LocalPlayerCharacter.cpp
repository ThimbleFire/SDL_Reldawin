#include "LocalPlayerCharacter.h"

LocalPlayerCharacter::LocalPlayerCharacter(const std::string& imagePath, Vector2i initialPosition) 
: Size(32, 32) {
    transform.position = initialPosition;    
    spriteTexture = g_resourceRepository.load(imagePath);
    if (spriteTexture == nullptr) {
        printf("Failed to load texture!\n");
    }            
}

void LocalPlayerCharacter::HandleInput(InputEvent& event) {
    if(event.handled == false)
        event.handled = true;
}

void LocalPlayerCharacter::Draw() const {
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
    SDL_RenderCopy(g_resourceRepository.renderer, spriteTexture, nullptr, &destRect);
}

void LocalPlayerCharacter::Update() {

}

void LocalPlayerCharacter::dispose() const {
    g_resourceRepository.unload("res/sprite.png");
}