#ifndef _UILABEL_H_
#define _UILABEL_H_

#include "UIElement.h"
#include <SDL2/SDL_ttf.h>

class UILabel : public UIElement {
    public:
        UILabel(const std::string& text, const std::string& fontPath) : text(text), fontPath(fontPath) {
            font = TTF_OpenFont(fontPath.c_str(), 9);
            CreateTexture();
            Redraw();
            transform.resizeWithParent = false;
        }

        ~UILabel() {
            SDL_DestroyTexture(texture);
            TTF_CloseFont(font);
        }

        void Draw() const override {
            SDL_RenderCopy(g_resourceRepository.renderer, texture, nullptr, &destRect);
        }

        void SetText(const std::string& text) {
            this->text = text;
            CreateTexture();
            Redraw();
        }

        void SetSize(int value) {
            TTF_CloseFont(font);
            delete font;
            font = nullptr;
            font = TTF_OpenFont(fontPath.c_str(), value);
            CreateTexture();
            Redraw();
        }
    public:
        TTF_Font* font = nullptr;

    private:
        void CreateTexture() {
            if (texture != nullptr) {
                SDL_DestroyTexture(texture);
            }
            SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(g_resourceRepository.renderer, surface);
            transform.SetSize(surface->w, surface->h);
            SDL_FreeSurface(surface);
        }

    private:
        std::string text;
        std::string fontPath;
        SDL_Texture* texture = nullptr;
        SDL_Color color = { 255, 255, 255, 200 };
};

#endif