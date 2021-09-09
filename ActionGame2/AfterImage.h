#pragma once

class AfterImage : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	ColorShader* colorShader = NULL;

	D3DXVECTOR2 destScale = { 0, 0 };
	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;

	int effectNum = 0;

	AfterImage(Sprite spr, RenderInfo ri, float visibleTime, D3DXCOLOR color);
	AfterImage(Sprite spr, RenderInfo ri, D3DXVECTOR2 destScale, D3DXCOLOR color);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

