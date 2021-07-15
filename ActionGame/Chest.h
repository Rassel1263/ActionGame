#pragma once
class Chest : public Object
{
public:
	std::vector<Sprite> spr;
	RenderInfo ri;

	int renderNum = 0;

	Chest(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& other) override;
};

