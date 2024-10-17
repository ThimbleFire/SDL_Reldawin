#include "SceneObject.h"
#include "Vector2i.h"
#include "Camera.h"
#include "ResourceRepository.h"

class LocalPlayerCharacter : public SceneObject {
    public:
        LocalPlayerCharacter(const std::string& imagePath, Vector2i initialPosition);
        ~LocalPlayerCharacter() = default;

        void Draw() const override;
        void HandleInput(InputEvent& event) override;
        void Update() override;
        void dispose() const override;

    private:
        const Vector2i Size;  // Size of the character (32x48 pixels)
        SDL_Texture* spriteTexture;
};