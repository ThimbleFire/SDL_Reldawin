#include "ResourceRepository.h"

// Define the global instance
ResourceRepository g_resourceRepository;

ResourceRepository::~ResourceRepository() {
    dispose();  // Clean up resources on destruction
}

SDL_Texture* ResourceRepository::load(const std::string& path, SDL_Renderer* renderer) {
    // Check if the texture is already loaded
    auto it = textures.find(path);
    if (it != textures.end()) {
        it->second.refCount++;  // Increment reference count
        return it->second.texture;
    }

    // Load image from file
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        std::cerr << "Unable to load image " << path << "! IMG_Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Create texture from surface
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!newTexture) {
        std::cerr << "Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);  // Clean up surface if texture creation fails
        return nullptr;
    }

    // Store texture and initialize reference count
    textures[path] = { newTexture, 1 };

    SDL_FreeSurface(loadedSurface);  // Free the loaded surface
    return newTexture;
}

void ResourceRepository::unload(const std::string& path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        it->second.refCount--;  // Decrement the reference count
        if (it->second.refCount <= 0) {
            // If reference count hits zero, destroy the texture
            SDL_DestroyTexture(it->second.texture);
            textures.erase(it);  // Remove it from the map
        }
    } else {
        std::cerr << "Warning: Tried to unload a texture that isn't loaded: " << path << std::endl;
    }
}

void ResourceRepository::dispose() {
    // Iterate through all textures and destroy them
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second.texture);  // Free each texture
    }
    textures.clear();  // Clear the map after cleaning up
}
