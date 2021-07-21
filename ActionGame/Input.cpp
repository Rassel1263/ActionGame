#include "DXUT.h"

void Input::Start()
{
    memset(m_KeyCur, 0, sizeof(m_KeyCur));
    memset(m_KeyCur, 0, sizeof(m_KeyOld));
    memset(m_KeyCur, 0, sizeof(m_KeyMap));

    SetKeyboardState(m_KeyCur);
}

int Input::Update()
{
    int i = 0;

    memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));

    memset(m_KeyCur, 0, sizeof(m_KeyCur));
    memset(m_KeyMap, 0, sizeof(m_KeyMap));

    GetKeyboardState(m_KeyCur);

    for (i = 0; i < 256; ++i)
    {
        BYTE vKey = m_KeyCur[i] & 0x80;
        m_KeyCur[i] = (vKey) ? 1 : 0;

        INT nOld = m_KeyOld[i];
        INT nCur = m_KeyCur[i];

        if (0 == nOld && 1 == nCur)	m_KeyMap[i] = InputState::INPUT_DOWN;	
        else if (1 == nOld && 0 == nCur)	m_KeyMap[i] = InputState::INPUT_UP;	
        else if (1 == nOld && 1 == nCur)	m_KeyMap[i] = InputState::INPUT_PRESS;	
        else	m_KeyMap[i] = InputState::INPUT_NONE;
    }

    return 0;
}

bool Input::KeyDown(int key)
{
    return (m_KeyMap[key] == InputState::INPUT_DOWN);
}

bool Input::KeyUp(int key)
{
    return (m_KeyMap[key] == InputState::INPUT_UP);
}

bool Input::KeyPress(int key)
{
    return (m_KeyMap[key] == InputState::INPUT_PRESS);
}

bool Input::GetMouse(Mouse mouse)
{
    return mouseState[(int)mouse];
}

void Input::SetMouse(Mouse mouse, int n)
{
    mouseState[(int)mouse] = n;
}
