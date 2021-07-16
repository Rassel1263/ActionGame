#pragma once
class BossIdle : public CState<Boss>
{
public:
	int pattern = -1;
	float restTime = 0.5f;

	static BossIdle* instance;

	virtual void EnterState(Boss* obj);
	virtual void UpdateState(Boss* obj, float deltaTime);
	virtual void ExitState(Boss* obj);
};

class BossBack : public CState<Boss>
{
public:
	float eftTimer = 0.0f;

	static BossBack* instance;

	virtual void EnterState(Boss* obj);
	virtual void UpdateState(Boss* obj, float deltaTime);
	virtual void ExitState(Boss* obj);
};

class BossWalk : public CState<Boss>
{
public:
	static BossWalk* instance;

	virtual void EnterState(Boss* obj);
	virtual void UpdateState(Boss* obj, float deltaTime);
	virtual void ExitState(Boss* obj);
};

class BossDash : public CState<Boss>
{
public:
	float eftTimer = 0.0f;

	static BossDash* instance;

	virtual void EnterState(Boss* obj);
	virtual void UpdateState(Boss* obj, float deltaTime);
	virtual void ExitState(Boss* obj);
};

class BossLAttack : public CState<Boss>
{
public:
	static BossLAttack* instance;

	virtual void EnterState(Boss* obj);
	virtual void UpdateState(Boss* obj, float deltaTime);
	virtual void ExitState(Boss* obj);
};

class BossHAttack : public CState<Boss>
{
public:
	static BossHAttack* instance;

	virtual void EnterState(Boss* obj);
	virtual void UpdateState(Boss* obj, float deltaTime);
	virtual void ExitState(Boss* obj);
};

class BossHit : public CState<Boss>
{
public: 
	bool miss = false;

	static BossHit* instance;

	virtual void EnterState(Boss* obj);
	virtual void UpdateState(Boss* obj, float deltaTime);
	virtual void ExitState(Boss* obj);
};

class BossDie : public CState<Boss>
{
	static BossDie* instance;

	virtual void EnterState(Boss* obj);
	virtual void UpdateState(Boss* obj, float deltaTime);
	virtual void ExitState(Boss* obj);
};



