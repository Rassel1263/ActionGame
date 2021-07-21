#pragma once
class Font : public Object
{
public:
	std::vector<Sprite> fonts;
	RenderInfo ri;

	std::wstring font;

	float* num = NULL;
	float interval = 0.0f;

	Font(std::wstring font, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float interval, float* num);
	Font(std::wstring font, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float interval, float num);
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

