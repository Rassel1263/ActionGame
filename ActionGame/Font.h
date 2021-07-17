#pragma once
class Font : public Object
{
public:
	std::vector<Sprite> fonts;
	RenderInfo ri;

	std::wstring font;
	float* num = NULL;

	Font(std::wstring font, D3DXVECTOR2 pos, float* num);
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

