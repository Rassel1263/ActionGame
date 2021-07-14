#pragma once
class AttackCollider : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	Units* obj = NULL;

	D3DXVECTOR2 attackVec = { 0, 0 };
	float visibleTime = 0.02f;

	AttackCollider(Units* obj, D3DXVECTOR2 offset, D3DXVECTOR2 attackVec);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& other) override;


};

