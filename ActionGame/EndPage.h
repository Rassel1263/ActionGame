#pragma once
class DiePage : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	DiePage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

