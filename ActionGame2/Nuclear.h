#pragma once
class Nuclear : public Object
{
public:
	bool ready = true;
	bool onAttack = false;

	Sprite spr;
	RenderInfo ri;

	Nuclear(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

