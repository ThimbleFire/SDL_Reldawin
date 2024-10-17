#ifndef RESOURCEREPOSITORY_H
#define RESOURCEREPOSITORY_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <iostream>

class ResourceRepository {
public:
    ~ResourceRepository();

    SDL_Texture* load(const std::string& path, SDL_Renderer* renderer);
    void unload(const std::string& path);  // Decrease reference count, unload if zero
    void dispose();  // Unload all textures

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
