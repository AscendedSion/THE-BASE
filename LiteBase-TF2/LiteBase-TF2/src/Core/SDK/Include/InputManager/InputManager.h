#pragma once
#include "../../../Utils/Utils.h"

//credits: https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/olcPixelGameEngine.h

struct Button_t {
	bool bPressed = false;
	bool bHeld = false;
	bool bReleased = false;
};

enum EKey
{
	KEY_NONE,
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
	KEY_K0, KEY_K1, KEY_K2, KEY_K3, KEY_K4, KEY_K5, KEY_K6, KEY_K7, KEY_K8, KEY_K9,
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
	KEY_SPACE, KEY_TAB, KEY_SHIFT, KEY_CTRL, KEY_INS, KEY_DEL, KEY_HOME, KEY_END, KEY_PGUP, KEY_PGDN,
	KEY_BACK, KEY_ESCAPE, KEY_RETURN, KEY_ENTER, KEY_PAUSE, KEY_SCROLL,
	KEY_NP0, KEY_NP1, KEY_NP2, KEY_NP3, KEY_NP4, KEY_NP5, KEY_NP6, KEY_NP7, KEY_NP8, KEY_NP9,
	KEY_NP_MUL, KEY_NP_DIV, KEY_NP_ADD, KEY_NP_SUB, KEY_NP_DECIMAL, KEY_PERIOD,
	KEY_EQUALS, KEY_COMMA, KEY_MINUS,
	KEY_OEM_1, KEY_OEM_2, KEY_OEM_3, KEY_OEM_4, KEY_OEM_5, KEY_OEM_6, KEY_OEM_7, KEY_OEM_8,
	KEY_CAPS_LOCK, KEY_ENUM_END
};

class CInputManager
{
private:
	bool pKeyNewState[256] = { 0 };
	bool pKeyOldState[256] = { 0 };
	Button_t pKeyboardState[256] = { 0 };

	bool pMouseOldState[5] = { 0 };
	bool pMouseNewState[5] = { 0 };
	Button_t pMouseState[5] = { 0 };

	int	nMouseWheelDelta = 0;
	int	nMouseWheelDeltaCache = 0;

	std::map<size_t, uint8_t> mapKeys;

private:
	void UpdateKeyState(int key, bool state);
	void UpdateMouseState(int button, bool state);
	void UpdateMouseWheel(int delta);

public:
	CInputManager();
	void WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Process();
	Button_t GetKey(EKey k) const;
	Button_t GetMouse(short b) const;
	int GetMouseWheel() const;
};

inline CInputManager g_InputManager;

#define GET_KEY(x) g_InputManager.GetKey(x)
#define GET_MOUSE(x) g_InputManager.GetMouse(x)
#define GET_WHEEL g_InputManager.GetMouseWheel()