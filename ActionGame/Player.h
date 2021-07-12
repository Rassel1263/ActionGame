#pragma once
class Player : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

