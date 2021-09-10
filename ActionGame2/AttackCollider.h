#pragma once
class AttackCollider : public Object
{
public:
	D3DXVECTOR2* fallowPos = NULL;
	D3DXVECTOR2 offset = { 0, 0 };

	D3DXVECTOR2 attackPower = { 0, 0 };
	float yVec = 0.0f;
	float damage = 0.0f;
	float collisionTime = 0.0f;
	D3DXVECTOR2 attackVector = { 0, 0 };
	D3DXVECTOR2 ownerPos = { 0, 0 };

	std::wstring tag = L"";

	AttackCollider(std::wstring team, D3DXVECTOR2 pos, D3DXVECTOR2 offset, Collider::AABB aabb, float damage, D3DXVECTOR2 attackPower, float yVec, float collisionTime, float groundPos);
	AttackCollider(std::wstring team, D3DXVECTOR2* pos, D3DXVECTOR2 offset, Collider::AABB aabb, float damage, D3DXVECTOR2 attackPower, float yVec, float collisionTime, float groundPos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

