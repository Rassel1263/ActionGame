#pragma once
class ResultScreen : public Object
{
public:
	Sprite fade;
	RenderInfo ri;

	ResultScreen();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

