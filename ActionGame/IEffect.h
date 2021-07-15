#pragma once
class IEffect : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float visibleTime = 0.0f;
	float timer = 0.0f;
	bool spectrum = false;

	IEffect(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float visibleTime);

	virtual void Update(float deltaTime);
	virtual void Render();
};

