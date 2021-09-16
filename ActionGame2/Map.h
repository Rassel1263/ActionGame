#pragma once
class Map : public Object
{
public:
	int widthRatio = 0;

	Sprite layer1;
	RenderInfo ri;

	Sprite layer2;

	Sprite layer3;

	Map(int widthRatio);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

