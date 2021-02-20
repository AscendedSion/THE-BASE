#include "AutoJump.h"

bool CAutoJump::ShouldRun(CTFPlayer *pLocal)
{
	if (pLocal->deadflag())
		return false;

	return true;
}

void CAutoJump::Run(CUserCmd *pCmd)
{
	if (auto pLocal = g_EntityCache.GetLocal())
	{
		if (!ShouldRun(pLocal))
			return;

		static bool bJumpState = false;

		if (pCmd->buttons & IN_JUMP)
		{
			if (!bJumpState && !(pLocal->m_fFlags() & FL_ONGROUND))
				pCmd->buttons &= ~IN_JUMP;

			else if (bJumpState)
				bJumpState = false;
		}

		else if (!bJumpState)
			bJumpState = true;
	}
}