#pragma once

template <typename T>
class CState
{
public:
	virtual void EnterState(T* obj) {}
	virtual void UpdateState(T* obj, float deltaTime) {}
	virtual void ExitState(T* obj) {}
};

