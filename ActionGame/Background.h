#pragma once
class Background : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	Background();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

