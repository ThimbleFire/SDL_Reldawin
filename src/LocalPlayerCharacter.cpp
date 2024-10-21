#include "LocalPlayerCharacter.h"

LocalPlayerCharacter::~LocalPlayerCharacter() {
    g_resourceRepository.unload("res/sprite.png");
}

LocalPlayerCharacter::LocalPlayerCharacter(const std::string& imagePath, Vector2i initialPosition) 
: Size(32, 32) {
    transform.position = initialPosition;    
    spriteTexture = g_resourceRepository.load(imagePath);
    if (spriteTexture == nullptr) {
        printf("Failed to load texture!\n");
    }            
}

void LocalPlayerCharacter::HandleInput(InputEvent& event) {
    //if(event.handled) return;
        
    if (event.event.type == SDL_KEYDOWN)
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        Vector2i inputVector(
            state[SDL_SCANCODE_A] ? -1 : state[SDL_SCANCODE_D] ? 1 : 0,
            state[SDL_SCANCODE_S] ? 1 : state[SDL_SCANCODE_W] ? -1 : 0 
        );
        Vector2 dir = Math::ToIsometric(inputVector);
        transform.Translate(dir);
        event.handled = true;
    }
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