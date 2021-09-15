#pragma once

class CBoss;
class BossUI : public ObjectUI
{
public:
	Sprite hp;
	Sprite hpBck;
	RenderInfo hpRI;

	Sprite sp;
	Sprite spBck;
	RenderInfo spRI;

	CBoss* boss = NULL;

	bool start = false;
	BossUI(CBoss* boss);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void SetSprite(std::wstring name, Sprite& spr);
};

