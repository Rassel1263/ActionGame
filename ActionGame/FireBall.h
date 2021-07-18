#pragma once
class FireBall : public Object
{
public:
	Sprite spr;
	RenderInfo ri;
	std::wstring name;

	float damage = 0;

	FireBall(std::wstring name, D3DXVECTOR2 pos, D3DXVECTOR2 dir, float damage, float z);
	 
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& other) override;
};

