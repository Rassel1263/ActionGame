#pragma once
class Effect : public Object
{
public:
	Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float aniTime, int atkScene = 0, bool bCamera = true, std::function<void()> func = NULL);
	Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float visibleTime, bool bCamera, std::function<void()> func = NULL);
	Effect(std::wstring eftName, D3DXVECTOR2* pos, D3DXVECTOR2 scale, D3DXVECTOR2 offset, float visibleTime, std::function<void()> func = NULL);

	Sprite spr;
	RenderInfo ri;

	std::function<void()> func = NULL;
	bool onAttack = false;
	int atkScene = 0;
	int effectNum = 0;
	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;

	D3DXVECTOR2* fallowPos = NULL;
	D3DXVECTOR2 offset = { 0, 0 };

public:
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

