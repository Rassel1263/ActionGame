#include "DXUT.h"
#include "LoadSprite.h"

LoadSprite::LoadSprite()
{
    loadingBar.LoadAll(L"Assets/Sprites/UI/IntroPro.png");
    loadingFrame.LoadAll(L"Assets/Sprites/UI/IntroProBck.png");
    loadingBar.widthRatio = 0.0f;

    TextureManager::GetInstance().SaveFilePath();

    for (int i = 0; i < 12; i++)
        threads.emplace_back(&TextureManager::LoadTexture, &TextureManager::GetInstance(), i);

    maxSize = TextureManager::GetInstance().filePaths.size();
}

LoadSprite::~LoadSprite()
{
    for (auto& thread : threads)
    {
        if (thread.joinable())
            thread.join();
    }
}

void LoadSprite::Update(float deltaTime)
{
    size = TextureManager::GetInstance().filePaths.size();

    if (TextureManager::GetInstance().textureLoad)
    {
        loadingBar.color.a -= deltaTime;

        if (loadingBar.color.a <= 0.0f)
        {
            nowScene->obm.AddObject(new Main());
            destroy = true;
        }
    }

    loadingBar.widthRatio = 1 - size / (float)maxSize;
}

void LoadSprite::Render()
{
    loadingFrame.Render(RenderInfo{ D3DXVECTOR2(0, 0)});
    loadingBar.Render(RenderInfo{ D3DXVECTOR2(-14, -9)});
}

