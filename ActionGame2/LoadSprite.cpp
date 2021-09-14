#include "DXUT.h"

void LoadSprite::Init()
{
	intro.LoadAll(L"Assets/Sprites/UI/Intro", 0.02f, false);

	progress.LoadAll(L"Assets/Sprites/UI/IntroPro.png");
	progressBck.LoadAll(L"Assets/Sprites/UI/IntroProBck.png");

	maxSize = TextureManager::GetInstance().filePaths.size();

}

void LoadSprite::Update(float deltaTime)
{
	intro.Update(deltaTime);

	size = TextureManager::GetInstance().filePaths.size();
	progress.widthRatio = 1 - size / (float)maxSize;

	Camera::GetInstance().Update(deltaTime);
}

void LoadSprite::Render()
{
	intro.Render(RenderInfo{D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2)});

	progressBck.Render(RenderInfo{D3DXVECTOR2(0, -200)});
	progress.Render(RenderInfo{D3DXVECTOR2(-14, -209)});
}
