#include "DXUT.h"
#include "Map.h"

Map::Map()
{
	layer1.LoadAll(L"Assets/Sprites/map/" + std::to_wstring(nowScene->curStage) + L"/layer1");

	layer2.LoadAll(L"Assets/Sprites/map/" + std::to_wstring(nowScene->curStage) + L"/layer2");
	layer3.LoadAll(L"Assets/Sprites/map/" + std::to_wstring(nowScene->curStage) + L"/layer3");

	layer2.bCamera = false;
	layer2.widthRatio = 7.0f;

	layer3.bCamera = false;
	layer3.widthRatio = 7.0f;

	layer = -10;
}

void Map::Update(float deltaTime)
{
}

void Map::Render()
{
	layer3.Render(RenderInfo{ D3DXVECTOR2(-Camera::GetInstance().cameraPos.x / 10, 0) });
	layer2.Render(RenderInfo{ D3DXVECTOR2(-Camera::GetInstance().cameraPos.x / 5, 0) });

	for (int i = 0; i < 7; ++i)
	{
		layer1.scene = 0;
		layer1.Render(RenderInfo{ D3DXVECTOR2(i * 3960, 0) });
	}
}
