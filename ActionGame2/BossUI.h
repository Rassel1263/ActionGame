#pragma once

class Boss1;
class BossUI : public ObjectUI
{
public:
	Sprite hp;
	Sprite hpBck;
	RenderInfo hpRI;

	Boss1* boss = NULL;

	bool start = false;
	BossUI(Boss1* boss);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

