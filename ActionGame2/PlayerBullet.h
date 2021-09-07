#pragma once
class PlayerBullet : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float damage = 5.0f;
	float speed = 0.0f;

	D3DXVECTOR2 dir = { 0, 0 };

	PlayerBullet(D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed, float damage);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

