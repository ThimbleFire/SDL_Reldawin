#include "SceneObject.h"
#include "Vector2i.h"
#include "Camera.h"
#include "ResourceRepository.h"
#include "TileMaster.h"
#include "Math.h"

class LocalPlayerCharacter : public SceneObject {
    public:
        //Event onChunkChange;

    public:
        LocalPlayerCharacter(const std::string& imagePath, Vector2i initialPosition, TileMaster* tileMaster);
        ~LocalPlayerCharacter();

        void Draw() const override;
        void HandleInput(InputEvent& event) override;
        void Update() override;

        Vector2i cell_global() const {
            return Math::WorldToCell(transform.position);
        }
        Vector2i chunk_position() const {
            Vector2i cell = cell_global();
            return Vector2i(cell.x / CHUNK_SIZE, cell.y / CHUNK_SIZE);
        }

    private:
        Vector2i last_chunk = Vector2i::ZERO;
        TileMaster* tileMaster;
        SDL_Texture* spriteTexture;
};
