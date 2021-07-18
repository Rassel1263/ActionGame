#pragma once
class HelpPage : public Object
{ 
public:
	Sprite page;
	RenderInfo ri;

	Sprite arrow;

	HelpPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

