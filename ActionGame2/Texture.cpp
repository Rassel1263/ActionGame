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

void TextureManager::SaveFilePath()
{
    for (auto& file : std::filesystem::recursive_directory_iterator(L"Assets/Sprites"))
    {
        std::wstring filePath = std::filesystem::absolute(file.path());
        std::transform(filePath.begin(), filePath.end(), filePath.begin(), std::towlower);

        filePaths.push(filePath);
    }

    fileSize = filePaths.size();
}

void TextureManager::Term()
{
   //for (auto texture : textures)
   //{
   //    SAFE_RELEASE(texture.second->src);
   //    SAFE_DELETE(texture.second);
   //}
}

void TextureManager::LoadTexture(int n)
{
    while (true)
    {
        std::wstring filePath;
        {

            std::lock_guard<std::mutex> gaurd(lock);

            if (filePaths.empty())
                break;

            wchar_t temp[256] = L"";
            wsprintfW(temp, L"thread : %d    FilePath : %s             filePathSize : %d\n", n, filePath.c_str(), (int)filePaths.size());
            OutputDebugString(temp);

            filePath = filePaths.front();
            filePaths.pop();
        }

        TextureManager::GetInstance().GetTexture(filePath);
    }

    ++threadCount;
    std::cout << threadCount << std::endl;
}

const Texture* TextureManager::GetTexture(std::wstring filePath)
{
    filePath = std::filesystem::absolute(filePath);
    std::transform(filePath.begin(), filePath.end(), filePath.begin(), std::towlower);

    auto tf = textures.find(filePath);

    if (tf != textures.end())
        return tf->second;

    Texture* texture = new Texture;

    if (FAILED(D3DXCreateTextureFromFileExW(DXUTGetD3D9Device(),
        filePath.c_str(),
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        1,
        0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        &texture->info,
        0,
        &texture->src)))
    {
        std::wstring path = filePath + L"\n";
        OutputDebugString(path.c_str());
        delete texture;
        return nullptr;
    }
    std::lock_guard<std::mutex> gaurd(insertLock);

    return textures.insert({ filePath, texture }).first->second;
}

void TextureManager::ResetDevice()
{
    for (auto texture : textures)
    {
        SAFE_RELEASE(texture.second->src);
        if (FAILED(D3DXCreateTextureFromFileExW(DXUTGetD3D9Device(),
            texture.first.c_str(),
            D3DX_DEFAULT_NONPOW2,
            D3DX_DEFAULT_NONPOW2,
            0,
            0,
            D3DFMT_A8R8G8B8,
            D3DPOOL_DEFAULT,
            D3DX_DEFAULT,
            D3DX_DEFAULT,
            0,
            &texture.second->info,
            0,
            &texture.second->src)))
        {
            texture.second->src = nullptr;
        }
    }
}
