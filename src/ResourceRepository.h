// ResourceRepository.h
#ifndef _RESOURCE_REPOSITORY_H
#define _RESOURCE_REPOSITORY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <iostream>

class ResourceRepository {
public:
    ResourceRepository() {}
    ~ResourceRepository();
    SDL_Texture* load(const std::string& path, SDL_Renderer* renderer);
    void dispose();
    void unload(const std::string& path);

private:
    std::map<std::string, SDL_Texture*> textures; // Map to store loaded textures
};

// Declare the global instance here
extern ResourceRepository g_resourceRepository;

#endif // _RESOURCE_REPOSITORY_H
