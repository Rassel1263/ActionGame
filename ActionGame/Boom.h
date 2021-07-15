#pragma once
class Boom : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	bool ignition = false;

	float timer = 0.0f;

	Boom(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float timer);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& other) override;
};

