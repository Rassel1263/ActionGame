#pragma once
class Effect : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float visibleTime = 0.0f;
	float timer = 0.0f;

	Effect(Sprite spr, D3DXVECTOR2 scale, D3DXVECTOR2 pos, float visibleTime);

	virtual void Update(float deltaTime);
	virtual void Render();
};

