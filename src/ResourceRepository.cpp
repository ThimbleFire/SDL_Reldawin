// ResourceRepository.cpp
#include "ResourceRepository.h"

// Define the global instance
ResourceRepository g_resourceRepository;

ResourceRepository::~ResourceRepository() {
    // Clean up resources here if needed
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
}

SDL_Texture* ResourceRepository::load(const std::string& path, SDL_Renderer* renderer) {
    // Check if texture is already loaded
    if (textures.find(path) != textures.end()) {
        return textures[path];
    }

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! IMG_Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Create texture from surface pixels
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        textures[path] = newTexture; // Store the texture in the map
    }

    // Free old loaded surface
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void ResourceRepository::dispose() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second); // Free the texture
    }
    textures.clear(); // Clear the map
}

void ResourceRepository::unload(const std::string& path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        SDL_DestroyTexture(it->second);
        textures.erase(it);
    }
}