#pragma once

class Player;
class PlayerUI : public ObjectUI
{
public:
	Player* player = NULL;

	Sprite base;

	Sprite hp;
	Sprite hpBck;
	RenderInfo hpRI;

	Sprite mp;
	Sprite mpBck;
	RenderInfo mpRI;

	Sprite comboFont;

	Sprite comboBck;
	Sprite comboGauge;
	RenderInfo comboRI;

	std::vector<Sprite> combo;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void UpdateCombo();
	void Load(std::wstring image, Sprite& spr);
};

