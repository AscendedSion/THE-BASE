#pragma once
#include "../../SDK/SDK.h"

class CAutoJump
{
private:
	bool ShouldRun(CTFPlayer *pLocal);

public:
	void Run(CUserCmd *pCmd);
};

inline CAutoJump g_AutoJump;