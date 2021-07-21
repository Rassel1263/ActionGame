#pragma once
class MainBackground : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	std::vector<Sprite> button;

	int curBtn = 1;

	MainBackground();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

