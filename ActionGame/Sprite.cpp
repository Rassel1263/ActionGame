#include "DXUT.h"
#include "Sprite.h"

namespace fs = std::filesystem;

Sprite::~Sprite()
{
    if (drawRect)
        delete drawRect;
}

void Sprite::LoadAll(std::wstring filePath, float aniMaxTime, bool aniLoop)
{
    textures.clear();

    if (fs::is_directory(filePath))
    {
        for (auto file : fs::recursive_directory_iterator(filePath))
        {
            if (auto texture = TextureManager::GetInstance().GetTexture(file.path()))
                textures.push_back(texture);
        }
    }
    else
    {
        if (auto texture = TextureManager::GetInstance().GetTexture(filePath))
            textures.push_back(texture);
        else
            textures.push_back(TextureManager::GetInstance().GetTexture(L"ActionGame.jpg"));
    }

    szScene = (int)textures.size() - 1;
    this->bAniLoop = aniLoop;
    this->aniMaxTime = aniMaxTime;
    this->filePath = filePath;
}

void Sprite::Update(float deltaTime)
{
    if (!bAnimation) return;

    aniTime += deltaTime;

    if (aniTime >= aniMaxTime)
    {
        if (scene < szScene)
            scene++;
        else if (bAniLoop)
            scene = 0;
        else
            bAnimation = false;
    }
}

void Sprite::Render(const RenderInfo& ri)
{
    D3DXMATRIX matrix;
    D3DXVECTOR2 centerPos = { (float)GetNowScene()->info.Width * ri.pivot.x, (float)GetNowScene()->info.Height * ri.pivot.y };
    D3DXMatrixTransformation2D(&matrix, &centerPos, 0, &ri.scale, &centerPos, D3DXToRadian(ri.rotate), &(ri.pos - centerPos - D3DXVECTOR2(0.0f, Game::GetInstance().TaskHeight)));

    Game::GetInstance().pSprite->SetTransform(&matrix);
    Game::GetInstance().pSprite->Draw(GetNowScene()->src, drawRect, NULL, NULL, color);
    Game::GetInstance().pSprite->Flush();
}

const Texture* Sprite::GetNowScene()
{
    return textures[scene];
}

void Sprite::Reset()
{
    bAnimation = true;
    aniTime = 0.0f;
    scene = 0;
}
