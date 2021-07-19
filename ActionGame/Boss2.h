#pragma once
class Boss2 : public Boss
{
public:
	/*CState<Boss2>* nowState = NULL;
	EnemyRange* enemyRange = NULL;*/

	Boss2(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

