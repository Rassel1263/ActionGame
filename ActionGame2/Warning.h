#pragma once
class Warning : public Object
{
public:
	Sprite bck;

	Sprite spr;
	RenderInfo ri;

	float timer = 0.0f;
	float maxTimer = 0.0f;

	Warning(std::wstring name, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float timer);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

