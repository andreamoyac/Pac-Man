#pragma once

#include "raylib.h"
#include "Globals.h"
#include <unordered_map>
#include <string>

enum class Resource {
    IMG_MENU,
    IMG_PLAYER, 
    IMG_TILES,
    IMG_ITEMS
};

class ResourceManager {
public:
    static ResourceManager& Instance()
    {
        static ResourceManager instance; 
        return instance;
    }

    AppStatus LoadTexture(Resource id, const std::string& file_path);
    void ReleaseTexture(Resource id);

    const Texture2D* GetTexture(Resource id) const;

    void Release();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    ResourceManager();
    ~ResourceManager();

    std::unordered_map<Resource, Texture2D> textures;
};