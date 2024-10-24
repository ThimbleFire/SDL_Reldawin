#include "Engine/SceneObject.h"
#include "Engine/Vector2i.h"
#include "Engine/Camera.h"
#include "Engine/ResourceRepository.h"
#include "Engine/TileMaster.h"
#include "Engine/Math.h"

class LocalPlayerCharacter : public SceneObject {
    public:
        //Event onChunkChange;

    public:
        LocalPlayerCharacter(const std::string& imagePath, Vector2i initialPosition, TileMaster* tileMaster);
        ~LocalPlayerCharacter();

        void Draw() const override;
        void HandleInput(InputEvent& event) override;
        void Update(float delta) override;

        Vector2i cell_global() const {
            return Math::WorldToCell(transform.position);
        }
        Vector2i chunk_position() const {
            Vector2i cell = cell_global();
            return Vector2i(cell.x / CHUNK_SIZE, cell.y / CHUNK_SIZE);
        }

    private:
        std::vector<Vector2> chain;
        Vector2i last_chunk = Vector2i::ZERO;
        TileMaster* tileMaster;
        SDL_Texture* spriteTexture;
};
