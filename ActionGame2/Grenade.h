#pragma once
class Grenade : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	Grenade(std::wstring team, D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

