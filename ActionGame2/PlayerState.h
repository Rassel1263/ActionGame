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

class PlayerSliding : public CState<Player>
{
public:
	static PlayerSliding* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};

class PlayerGunkata : public CState<Player>
{
public:
	float afterImageTime = 0.0f;

	static PlayerGunkata* GetInstance();

	virtual void EnterState(Player* obj) override;
	virtual void UpdateState(Player* obj, float deltaTime) override;
	virtual void ExitState(Player* obj) override;
};