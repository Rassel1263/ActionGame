#pragma once
class Map : public Object
{
public:
	Sprite layer1;
	RenderInfo ri;

	Sprite layer2;

	Sprite layer3;

	Map();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

