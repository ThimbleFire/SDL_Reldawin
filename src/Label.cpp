#include "Label.h"
#include <iostream>
#include "ResourceRepository.h"

Label::Label(const std::string& text, const std::string& fontPath, int fontSize, SDL_Color color)    
    : font(nullptr), color(color), text(text), texture(nullptr), width(0), height(0) {
        
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    } else {
        createTexture();
    }
}

Label::~Label() {
    // Clean up texture and font
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
}

void Label::createTexture() {
    // Clean up previous texture
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    // Render text to a surface
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface != nullptr) {
        // Create texture from surface
        texture = SDL_CreateTextureFromSurface(g_resourceRepository.renderer, surface);
        if (texture == nullptr) {
            std::cerr << "Unable to create texture from surface: " << SDL_GetError() << std::endl;
        } else {
            // Get width and height
            width = surface->w;
            height = surface->h;
        }
        SDL_FreeSurface(surface);
    } else {
        std::cerr << "Unable to render text to surface: " << TTF_GetError() << std::endl;
    }
}

void Label::Draw() const {
    
    SDL_Rect destRect = { transform.position.x, transform.position.y, width, height };
    SDL_RenderCopy(g_resourceRepository.renderer, texture, nullptr, &destRect);
}

void Label::setText(const std::string& newText) {
    text = newText;
    createTexture(); // Create a new texture with the updated text
}
