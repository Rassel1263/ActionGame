#pragma once
class Mp : public Object
{
public:
	float startTime = 0.0f;
	float startAngle = 0.0f;
	float angle = 0.0f;

	float turnSpeed = 0.0f;
	float turnTime = 0.0f;

	float amount = 0.0f;
	Sprite spr;
	RenderInfo ri;

	Mp(D3DXVECTOR2 pos, float startAngle, float amount);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

