#include "ResourceManager.h"


ResourceManager::ResourceManager(){}
ResourceManager::~ResourceManager(){Release();}

AppStatus ResourceManager::LoadTexture(Resource id, const std::string& file_path)
{
    Texture2D texture = ::LoadTexture(file_path.c_str());
    if (texture.id == 0)
    {
        LOG("Failed to load texture ", file_path);
        return AppStatus::ERROR;
    }
    
    textures[id] = texture;
    return AppStatus::OK;
}

void ResourceManager::ReleaseTexture(Resource id)
{
    auto it = textures.find(id);

    if (it != textures.end())
    {
        UnloadTexture(it->second);
        textures.erase(it);
    }
}

const Texture2D* ResourceManager::GetTexture(Resource id) const
{
    auto it = textures.find(id);
    if (it != textures.end())   return &(it->second);

    return nullptr;
}

void ResourceManager::Release()
{
    for (auto& pair : textures)
    {
        UnloadTexture(pair.second);
    }
    textures.clear();
}