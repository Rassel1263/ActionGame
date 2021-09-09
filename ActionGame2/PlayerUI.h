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

	Sprite combo;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void Load(std::wstring image, Sprite& spr);
};

