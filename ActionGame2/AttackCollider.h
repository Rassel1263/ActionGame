#pragma once
class AttackCollider : public Object
{
public:
	float attackPower = 0.0f;
	float yVec = 0.0f;
	float damage = 0.0f;
	float collisionTime = 0.0f;
	D3DXVECTOR2 attackVector = { 0, 0 };
	D3DXVECTOR2 ownerPos = { 0, 0 };

	std::wstring tag = L"";

	AttackCollider( std::wstring team, D3DXVECTOR2 pos, D3DXVECTOR2 offset, Collider::AABB aabb, float damage, float attackPower, float yVec, float collisionTime);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

