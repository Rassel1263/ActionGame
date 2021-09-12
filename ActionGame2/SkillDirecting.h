#pragma once
class SkillDirecting : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	bool fill = false;
	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;

	int skillNum = 0;

	SkillDirecting(float timer, int skillNum = 0);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

