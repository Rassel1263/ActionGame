#pragma once

enum class InputState
{
	INPUT_NONE = 0,
	INPUT_DOWN,
	INPUT_UP,
	INPUT_PRESS
};

enum class Mouse
{
	RMOUSE,
	LMOUSE
};

class Input : public Singleton<Input>
{
protected:
	BYTE m_KeyCur[256];
	BYTE m_KeyOld[256];
	InputState m_KeyMap[256];

	bool mouseState[2];

public:
	int wheelCount = 0;
	D3DXVECTOR2 mousePos = { 0, 0 };

	void Start();
	int Update();

	bool KeyDown(int key);
	bool KeyUp(int key);
	bool KeyPress(int key);
	bool GetMouse(Mouse mouse);
	void SetMouse(Mouse mouse, int n);
};