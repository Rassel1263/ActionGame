#include "DXUT.h"
#include "Font.h"

Font::Font(std::wstring font, D3DXVECTOR2 pos, float* num)
{
	this->font = font;
	std::wstring str = std::to_wstring((int)*num);
	this->pos = pos;
	this->num = num;
	int size = str.size();

	fonts.resize(size);
	for (int i = 0; i < size; ++i)
	{
		fonts[i].LoadAll(L"Assets/Sprites/UI/Font/" + font + L"/" + str.substr(i, 1) + L".png");
		fonts[i].bCamera = false;
	}
}

void Font::Update(float deltaTime)
{
	if (num)
	{
		std::wstring str = std::to_wstring((int)*num);
		int size = str.size();
		fonts.resize(size);

		for (int i = 0; i < size; ++i)
		{
			fonts[i].LoadAll(L"Assets/Sprites/UI/Font/" + font + L"/" + str.substr(i, 1) + L".png");
			fonts[i].bCamera = false;
		}
	}
}

void Font::Render()
{
	ri.pos = pos;
	int interval = 0;
	for (auto& spr : fonts)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(pos.x + interval * 18, pos.y) });
		interval++;
	}
}
