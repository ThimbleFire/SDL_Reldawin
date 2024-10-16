#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Label {
public:
    Label(const std::string& text, const std::string& fontPath, int fontSize, SDL_Color color, SDL_Renderer* renderer);
    ~Label();

    void render(int x, int y);
    void setText(const std::string& text);

private:
    std::string text;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Color color;
    int width;
    int height;

    void createTexture();
};

#endif // LABEL_H