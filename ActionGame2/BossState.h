#pragma once
class BossIdle : public CState<Boss1>
{
public:
	static BossIdle* GetInstance();

	// CState을(를) 통해 상속됨
	virtual void EnterState(Boss1* obj) override;
	virtual void UpdateState(Boss1* obj, float deltaTime) override;
	virtual void ExitState(Boss1* obj) override;
};

class BossMove : public CState<Boss1>
{
public:
	static BossMove* GetInstance();

	virtual void EnterState(Boss1* obj) override;
	virtual void UpdateState(Boss1* obj, float deltaTime) override;
	virtual void ExitState(Boss1* obj) override;
};

class BossHit : public CState<Boss1>
{
public:
	static BossHit* GetInstance();

	virtual void EnterState(Boss1* obj) override;
	virtual void UpdateState(Boss1* obj, float deltaTime) override;
	virtual void ExitState(Boss1* obj) override;
};

class BossPattern1 : public CState<Boss1>
{
public:
	static BossPattern1* GetInstance();

	virtual void EnterState(Boss1* obj) override;
	virtual void UpdateState(Boss1* obj, float deltaTime) override;
	virtual void ExitState(Boss1* obj) override;
};

class BossPattern2 : public CState<Boss1>
{
public:
	static BossPattern2* GetInstance();

	virtual void EnterState(Boss1* obj) override;
	virtual void UpdateState(Boss1* obj, float deltaTime) override;
	virtual void ExitState(Boss1* obj) override;
};

class BossPattern3 : public CState<Boss1>
{
public:
	static BossPattern3* GetInstance();

	virtual void EnterState(Boss1* obj) override;
	virtual void UpdateState(Boss1* obj, float deltaTime) override;
	virtual void ExitState(Boss1* obj) override;
};

class BossDie : public CState<Boss1>
{
public:
	static BossDie* GetInstance();

	virtual void EnterState(Boss1* obj) override;
	virtual void UpdateState(Boss1* obj, float deltaTime) override;
	virtual void ExitState(Boss1* obj) override;
};