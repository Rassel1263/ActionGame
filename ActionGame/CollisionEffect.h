#pragma once
class CollisionEffect : public IEffect
{
public:
	Units* owner = NULL;
	float hitTimer = 0.0f;
	float timer = 0.0f;
	bool hit = true;

	CollisionEffect(Units* obj, std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 min, D3DXVECTOR2 max, float visibleTime = 0.0f, float hitTimer = 999.0f);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& other);
};

