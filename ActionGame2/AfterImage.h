#pragma once
class AfterImage : public Object
{
public:
	Sprite spr;
	RenderInfo ri;
	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;

	AfterImage(Sprite spr, RenderInfo ri, D3DXVECTOR2 pos, float visibleTime, D3DXCOLOR color);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

