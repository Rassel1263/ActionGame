#include "DXUT.h"
#include "Texture.h"

TextureManager::~TextureManager()
{
    for (auto texture : textures)
    {
        SAFE_RELEASE(texture.second->src);
        SAFE_DELETE(texture.second);
    }
}

const Texture* TextureManager::GetTexture(std::wstring filePath)
{
    auto tf = textures.find(filePath);

    if (tf != textures.end())
        return tf->second;

    Texture* texture = new Texture();

    if (FAILED(D3DXCreateTextureFromFileExW(DXUTGetD3D9Device(),
        filePath.c_str(),
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        0,
        0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        &texture->info,
        0,
        &texture->src)))
    {
        delete texture;
        return nullptr;
    }

    return textures.insert({filePath, texture}).first->second;
}

void TextureManager::OnDestroy()
{
    /*for (auto texture : textures)
    {
        SAFE_RELEASE(texture.second->src);
    }*/
}

void TextureManager::Reset()
{
   /* for (auto texture : textures)
    {
        SAFE_RELEASE(texture.second->src);
        if (FAILED(D3DXCreateTextureFromFileExW(DXUTGetD3D9Device(),
            texture.first.c_str(),
            D3DX_DEFAULT_NONPOW2,
            D3DX_DEFAULT_NONPOW2,
            0,
            0,
            D3DFMT_A8R8G8B8,
            D3DPOOL_MANAGED,
            D3DX_DEFAULT,
            D3DX_DEFAULT,
            0,
            &texture.second->info,
            0,
            &texture.second->src)))
        {
            texture.second->src = nullptr;
        }
    }*/
}
