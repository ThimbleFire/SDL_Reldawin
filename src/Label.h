#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "SceneObject.h"

class Label : public SceneObject {
    public:
        Label(const std::string& text, const std::string& fontPath, int fontSize, SDL_Color color);
        ~Label();

        void Draw() const override;
        void setText(const std::string& text);
        void dispose() const override {
            
        }

    private:
        TTF_Font* font;
        SDL_Color color;
        std::string text;
        SDL_Texture* texture;
        int width;
        int height;

        void createTexture();
};

#endif // LABEL_H