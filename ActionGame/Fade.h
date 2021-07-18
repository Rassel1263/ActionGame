#pragma once
class Fade : public Object
{
public:
	Sprite fade;

	Sprite font;
	RenderInfo ri;

	Fade(int stage);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

