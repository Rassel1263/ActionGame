#pragma once
class BossIdle : public CState<CBoss>
{
public:
	static BossIdle* GetInstance();

	// CState��(��) ���� ��ӵ�
	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossMove : public CState<CBoss>
{
public:
	static BossMove* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossHit : public CState<CBoss>
{
public:
	static BossHit* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossStun : public CState<CBoss>
{
public:
	static BossStun* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossPattern1 : public CState<CBoss>
{
public:
	static BossPattern1* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossPattern2 : public CState<CBoss>
{
public:
	static BossPattern2* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossPattern3 : public CState<CBoss>
{
public:
	static BossPattern3* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};

class BossDie : public CState<CBoss>
{
public:
	bool restoration = false;
	float timer = 0.0f;

	static BossDie* GetInstance();

	virtual void EnterState(CBoss* obj) override;
	virtual void UpdateState(CBoss* obj, float deltaTime) override;
	virtual void ExitState(CBoss* obj) override;
};