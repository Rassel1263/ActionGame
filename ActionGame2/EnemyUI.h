#pragma once

class CEnemy;
class EnemyUI : public ObjectUI
{
public:
	Sprite hp;
	Sprite hpBck;
	RenderInfo hpRI;

	CEnemy* enemy = NULL;

	EnemyUI(CEnemy* enemy);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

