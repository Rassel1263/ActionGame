#pragma once
class UIAfterImage : public ObjectUI
{
public:
	Sprite spr;
	RenderInfo ri;

	ColorShader* colorShader = NULL;

	D3DXVECTOR2 destScale = { 0, 0 };

	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;

	float timer = 0.0f;

	int effectNum = 0;

	UIAfterImage(Sprite spr, RenderInfo ri, float visibleTime, D3DXCOLOR color, int layer);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

