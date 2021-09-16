#pragma once
#include "Bullet.h"

class EnhanceData : public Singleton<EnhanceData>
{
public:
	std::vector<bool> enHance;

	void Init()
	{
		enHance.resize(6);

		for (auto& e : enHance)
			e = false;
	}

	void SetData(int idx)
	{
		enHance.at(idx) = true;
	}

	void GetData(std::vector<bool>& vec)
	{
		std::copy(enHance.begin(), enHance.end(), std::back_inserter(vec));
	}
};

class Player : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,
		JUMP,
		FALL,
		LANDING,
		SLIDE,
		HIT,
		STUN,
		STANDUP,
		DIE,

		JUMPATTACK1,
		JUMPATTACK2,
		JUMPATTACK3,

		WEAKATTACK1,
		WEAKATTACK2,
		WEAKATTACK3,
		WEAKATTACK4,
		WEAKTATCKEND,

		GRENADE,
		STRONGATTACK,

		GUNKATA,
		MOVESHOOT,
		MACHINEGUN,
		SNIPER,
		NUCLEAR,

		SHADOW,
		END,
	};

	Player();

	CState<Player>* nowState = NULL;

	// ÄÞº¸ ½Ã½ºÅÛ
	std::vector<std::string> comboInputs;
	std::vector<bool> skillEnhance;

	bool attackCancel = false;
	bool specialAttack = false;
	bool invincible = false;
	float comboTimer = 0.0f;
	float cancelTimer = 0.0f;

	float mp = 0.0f;
	float maxMp = 100.0f;

	float healTimer = 0.0f;
	float healTime = 20.0f;

	bool powerUp = false;
	float powerUpTimer = 0.0f;

	bool grenade = false;

	// specialAttack
	int attackNum = 0;
	bool afterImage = false;
	float afterImageTime = 0.0f;
	float nuclearTime = 0.0f;

	bool nuclear = false;
	bool jump = false;
	bool jumpAttack = false;
	bool fallowCamera = true;

	int combo = 0;
	int prevCombo = 0;
	int maxCombo = 0;
	float comboInterval = 0.0f;

public:
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void SetImages() override;
	virtual void Hit(float damage, D3DXVECTOR2 addForce);
	
	void SetState(CState<Player>* nextState);
	void PlusMp(float value);
	void PlusHp(float value);
	void PlusCombo(int value);
	void ItemEffective(int index);
	void UpdateItem(float deltaTime);
	bool Move(float deltaTime, bool moveShot = false);

	void CancelUpdate(float deltaTime);
	void HealUpdate(float deltaTime);

	void Combo(float deltaTime);
	void ComboCheck();
	void ComboInputCheck();
	void ComboInput(unsigned char u, std::string name);
	void ComboChecking(int skillNum, int inputAmount, ...);

	void CreateBullet(D3DXVECTOR2 offset, float speed, float damage, Bullet::Type type, bool jumpShot = false);
	void CreateAttackCollider(int scene, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, D3DXVECTOR2 atkPower, float yVec, float time, bool fallow = false);
	void CreateAfterImage(int scene, float visibleTime, D3DXCOLOR color, bool fallow = true);
	void SetSpecialAttack(Images image,int attackScene, float afterImageTime, float mp);
	void SpecialAttackCancel();
};

