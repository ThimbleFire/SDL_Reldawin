#ifndef RESOURCEREPOSITORY_H
#define RESOURCEREPOSITORY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <iostream>

class ResourceRepository {
public:
    ~ResourceRepository();
    void Initialize(SDL_Renderer* renderer);
    SDL_Texture* load(const std::string& path);
    void unload(const std::string& path);  // Decrease reference count, unload if zero
    void dispose();  // Unload all textures
    SDL_Renderer* renderer;

private:
    // Struct to hold both texture and reference count
    struct TextureData {
        SDL_Texture* texture;
        int refCount;  // Reference count
    };

    // Map to store textures with reference counting
    std::map<std::string, TextureData> textures;
};

// Global instance for easy access
extern ResourceRepository g_resourceRepository;

#endif
