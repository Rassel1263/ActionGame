#pragma once
class Boom : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	Units* owner = NULL;

	float timer = 0.0f;

	Boom(Units* obj, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float timer);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

