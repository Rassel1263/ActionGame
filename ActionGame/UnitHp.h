#pragma once
class UnitHp : public Object
{
public:
	std::vector<Sprite> hp;
	std::vector<Sprite> eUpper;
	std::vector<Sprite> bUpper;
	RenderInfo pRI;
	RenderInfo eRI;

	UnitHp();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

