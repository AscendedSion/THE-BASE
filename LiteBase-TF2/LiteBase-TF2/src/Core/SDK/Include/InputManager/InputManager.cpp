#include "InputManager.h"

CInputManager::CInputManager()
{
	mapKeys[0x00] = EKey::KEY_NONE;
	mapKeys[0x41] = EKey::KEY_A; mapKeys[0x42] = EKey::KEY_B; mapKeys[0x43] = EKey::KEY_C; mapKeys[0x44] = EKey::KEY_D; mapKeys[0x45] = EKey::KEY_E;
	mapKeys[0x46] = EKey::KEY_F; mapKeys[0x47] = EKey::KEY_G; mapKeys[0x48] = EKey::KEY_H; mapKeys[0x49] = EKey::KEY_I; mapKeys[0x4A] = EKey::KEY_J;
	mapKeys[0x4B] = EKey::KEY_K; mapKeys[0x4C] = EKey::KEY_L; mapKeys[0x4D] = EKey::KEY_M; mapKeys[0x4E] = EKey::KEY_N; mapKeys[0x4F] = EKey::KEY_O;
	mapKeys[0x50] = EKey::KEY_P; mapKeys[0x51] = EKey::KEY_Q; mapKeys[0x52] = EKey::KEY_R; mapKeys[0x53] = EKey::KEY_S; mapKeys[0x54] = EKey::KEY_T;
	mapKeys[0x55] = EKey::KEY_U; mapKeys[0x56] = EKey::KEY_V; mapKeys[0x57] = EKey::KEY_W; mapKeys[0x58] = EKey::KEY_X; mapKeys[0x59] = EKey::KEY_Y;
	mapKeys[0x5A] = EKey::KEY_Z;

	mapKeys[VK_F1] = EKey::KEY_F1; mapKeys[VK_F2] = EKey::KEY_F2; mapKeys[VK_F3] = EKey::KEY_F3; mapKeys[VK_F4] = EKey::KEY_F4;
	mapKeys[VK_F5] = EKey::KEY_F5; mapKeys[VK_F6] = EKey::KEY_F6; mapKeys[VK_F7] = EKey::KEY_F7; mapKeys[VK_F8] = EKey::KEY_F8;
	mapKeys[VK_F9] = EKey::KEY_F9; mapKeys[VK_F10] = EKey::KEY_F10; mapKeys[VK_F11] = EKey::KEY_F11; mapKeys[VK_F12] = EKey::KEY_F12;

	mapKeys[VK_DOWN] = EKey::KEY_DOWN; mapKeys[VK_LEFT] = EKey::KEY_LEFT; mapKeys[VK_RIGHT] = EKey::KEY_RIGHT; mapKeys[VK_UP] = EKey::KEY_UP;
	mapKeys[VK_RETURN] = EKey::KEY_ENTER;

	mapKeys[VK_BACK] = EKey::KEY_BACK; mapKeys[VK_ESCAPE] = EKey::KEY_ESCAPE; mapKeys[VK_RETURN] = EKey::KEY_ENTER; mapKeys[VK_PAUSE] = EKey::KEY_PAUSE;
	mapKeys[VK_SCROLL] = EKey::KEY_SCROLL; mapKeys[VK_TAB] = EKey::KEY_TAB; mapKeys[VK_DELETE] = EKey::KEY_DEL; mapKeys[VK_HOME] = EKey::KEY_HOME;
	mapKeys[VK_END] = EKey::KEY_END; mapKeys[VK_PRIOR] = EKey::KEY_PGUP; mapKeys[VK_NEXT] = EKey::KEY_PGDN; mapKeys[VK_INSERT] = EKey::KEY_INS;
	mapKeys[VK_SHIFT] = EKey::KEY_SHIFT; mapKeys[VK_CONTROL] = EKey::KEY_CTRL;
	mapKeys[VK_SPACE] = EKey::KEY_SPACE;

	mapKeys[0x30] = EKey::KEY_K0; mapKeys[0x31] = EKey::KEY_K1; mapKeys[0x32] = EKey::KEY_K2; mapKeys[0x33] = EKey::KEY_K3; mapKeys[0x34] = EKey::KEY_K4;
	mapKeys[0x35] = EKey::KEY_K5; mapKeys[0x36] = EKey::KEY_K6; mapKeys[0x37] = EKey::KEY_K7; mapKeys[0x38] = EKey::KEY_K8; mapKeys[0x39] = EKey::KEY_K9;

	mapKeys[VK_NUMPAD0] = EKey::KEY_NP0; mapKeys[VK_NUMPAD1] = EKey::KEY_NP1; mapKeys[VK_NUMPAD2] = EKey::KEY_NP2; mapKeys[VK_NUMPAD3] = EKey::KEY_NP3; mapKeys[VK_NUMPAD4] = EKey::KEY_NP4;
	mapKeys[VK_NUMPAD5] = EKey::KEY_NP5; mapKeys[VK_NUMPAD6] = EKey::KEY_NP6; mapKeys[VK_NUMPAD7] = EKey::KEY_NP7; mapKeys[VK_NUMPAD8] = EKey::KEY_NP8; mapKeys[VK_NUMPAD9] = EKey::KEY_NP9;
	mapKeys[VK_MULTIPLY] = EKey::KEY_NP_MUL; mapKeys[VK_ADD] = EKey::KEY_NP_ADD; mapKeys[VK_DIVIDE] = EKey::KEY_NP_DIV; mapKeys[VK_SUBTRACT] = EKey::KEY_NP_SUB; mapKeys[VK_DECIMAL] = EKey::KEY_NP_DECIMAL;

	mapKeys[VK_OEM_1] = EKey::KEY_OEM_1;			// On US and UK keyboards this is the ';:' key
	mapKeys[VK_OEM_2] = EKey::KEY_OEM_2;			// On US and UK keyboards this is the '/?' key
	mapKeys[VK_OEM_3] = EKey::KEY_OEM_3;			// On US keyboard this is the '~' key
	mapKeys[VK_OEM_4] = EKey::KEY_OEM_4;			// On US and UK keyboards this is the '[{' key
	mapKeys[VK_OEM_5] = EKey::KEY_OEM_5;			// On US keyboard this is '\|' key.
	mapKeys[VK_OEM_6] = EKey::KEY_OEM_6;			// On US and UK keyboards this is the ']}' key
	mapKeys[VK_OEM_7] = EKey::KEY_OEM_7;			// On US keyboard this is the single/double quote key. On UK, this is the single quote/@ symbol key
	mapKeys[VK_OEM_8] = EKey::KEY_OEM_8;			// miscellaneous characters. Varies by keyboard
	mapKeys[VK_OEM_PLUS] = EKey::KEY_EQUALS;		// the '+' key on any keyboard
	mapKeys[VK_OEM_COMMA] = EKey::KEY_COMMA;		// the comma key on any keyboard
	mapKeys[VK_OEM_MINUS] = EKey::KEY_MINUS;		// the minus key on any keyboard
	mapKeys[VK_OEM_PERIOD] = EKey::KEY_PERIOD;		// the period key on any keyboard
	mapKeys[VK_CAPITAL] = EKey::KEY_CAPS_LOCK;
}

void CInputManager::UpdateKeyState(int key, bool state) {
	pKeyNewState[key] = state;
}

void CInputManager::UpdateMouseState(int button, bool state) {
	pMouseNewState[button] = state;
}

void CInputManager::UpdateMouseWheel(int delta) {
	nMouseWheelDeltaCache += delta;
}

void CInputManager::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYDOWN:		g_InputManager.UpdateKeyState(mapKeys[wParam], true); break;
		case WM_KEYUP:			g_InputManager.UpdateKeyState(mapKeys[wParam], false); break;
		case WM_SYSKEYDOWN:		g_InputManager.UpdateKeyState(mapKeys[wParam], true); break;
		case WM_SYSKEYUP:		g_InputManager.UpdateKeyState(mapKeys[wParam], false); break;
		case WM_LBUTTONDOWN:	g_InputManager.UpdateMouseState(0, true); break;
		case WM_LBUTTONUP:		g_InputManager.UpdateMouseState(0, false); break;
		case WM_RBUTTONDOWN:	g_InputManager.UpdateMouseState(1, true); break;
		case WM_RBUTTONUP:		g_InputManager.UpdateMouseState(1, false); break;
		case WM_MBUTTONDOWN:	g_InputManager.UpdateMouseState(2, true); break;
		case WM_MBUTTONUP:		g_InputManager.UpdateMouseState(2, false); break;
		case WM_MOUSEWHEEL:		g_InputManager.UpdateMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam)); break;
		default: break;
	}
}

void CInputManager::Process()
{
	auto ProcessKeys = [&](Button_t *pKeys, bool *pStateOld, bool *pStateNew, int nKeyCount)
	{
		for (int i = 0; i < nKeyCount; i++)
		{
			pKeys[i].bPressed = false;
			pKeys[i].bReleased = false;

			if (pStateNew[i] != pStateOld[i])
			{
				if (pStateNew[i]) {
					pKeys[i].bPressed = !pKeys[i].bHeld;
					pKeys[i].bHeld = true;
				}

				else {
					pKeys[i].bReleased = true;
					pKeys[i].bHeld = false;
				}
			}

			pStateOld[i] = pStateNew[i];
		}
	};

	ProcessKeys(pKeyboardState, pKeyOldState, pKeyNewState, 256);
	ProcessKeys(pMouseState, pMouseOldState, pMouseNewState, 5);

	nMouseWheelDelta = nMouseWheelDeltaCache;
	nMouseWheelDeltaCache = 0;
}

Button_t CInputManager::GetKey(EKey k) const {
	return pKeyboardState[k];
}

Button_t CInputManager::GetMouse(short b) const {
	return pMouseState[b];
}

int CInputManager::GetMouseWheel() const {
	return nMouseWheelDelta;
}