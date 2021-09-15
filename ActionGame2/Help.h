#pragma once
class Help : public Object
{
public:
	Sprite panel;
	Sprite bck;

	Help();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

