#pragma once

class PlayerIdle : public CState<Player>
{
public:
	static PlayerIdle* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerMove : public CState<Player>
{
public:
	static PlayerMove* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerJump : public CState<Player>
{
public:
	float afterImageTime = 0.0f;

	static PlayerJump* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerFall : public CState<Player>
{
public:
	static PlayerFall* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerLanding : public CState<Player>
{
public:
	static PlayerLanding* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerJumpAttack : public CState<Player>
{
public:
	float timer = 0.0f;
	int combo = 0;
	int comboInput = 0;

	static PlayerJumpAttack* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;

};

class PlayerWeakAttack : public CState<Player>
{
public:
	bool onAttack = false;
	float timer = 0.0f;
	int combo = 0;
	int comboInput = 0;

	static PlayerWeakAttack* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerStopWeakAttack : public CState<Player>
{
public:
	static PlayerStopWeakAttack* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerStrongAttack : public CState<Player>
{
public:
	static PlayerStrongAttack* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerSpecialAttack : public CState<Player>
{
public:
	float timer = 0.0f;
	bool canAttack = false;

	static PlayerSpecialAttack* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerHit : public CState<Player>
{
public:
	static PlayerHit* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};
