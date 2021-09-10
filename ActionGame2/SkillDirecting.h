#pragma once
class SkillDirecting : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	bool fill = false;
	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;

	SkillDirecting(float timer);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

