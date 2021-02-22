#include "Example.h"

void CExample::Run()
{
	if (auto pLocal = g_EntityCache.GetLocal())
	{
		if (pLocal->m_iTeamNum() < 2 || pLocal->deadflag() || I::EngineVGui->IsGameUIVisible())
			return;

		//thirdperson toggle
		{
			static bool bToggle = false;

			if (GetAsyncKeyState('R') & 1)
				pLocal->m_nForceTauntCam() = static_cast<int>(bToggle = !bToggle);
		}

		if (auto pWeapon = g_EntityCache.GetWeapon())
		{
			g_Draw.String(
				g_Fonts[EFonts::DEBUG].m_dwFont,
				200, 200,
				{ 255, 255, 255, 255 }, TXT_DEFAULT,
				L"pWeapon->CanHeadShot() -> %x", pWeapon->CanHeadShot(pLocal)
			);
		}
		
		for (auto pEntity : g_EntityCache.GetGroup(EEntGroup::PLAYERS_ALL))
		{
			auto pPlayer = pEntity->As<CTFPlayer>();

			if (pPlayer->deadflag())
				continue;

			Vec3 vScreen = {};

			if (!Utils::W2S(pPlayer->GetAbsOrigin() + Vec3(0.0f, 0.0f, 40.0f), vScreen))
				continue;

			bool bIsLocal = pPlayer == pLocal;

			Color_t DrawColor = [&]() -> Color_t
			{
				if (bIsLocal || G::IsFriend(pPlayer))
					return { 0, 255, 0, 255 };

				switch (pPlayer->m_iTeamNum()) {
					case 2: return { 255, 107, 107, 255 };
					case 3: return { 72, 219, 251, 255 };
					default: return { 255, 255, 255, 255 };
				}
			}();

			if (!bIsLocal)
			{
				Vec3 vHead = {};

				if (Utils::W2S(pPlayer->GetHitboxPos(HITBOX_HEAD), vHead))
				{
					g_Draw.Line(
						g_Draw.m_nScreenW / 2, g_Draw.m_nScreenH,
						static_cast<int>(vHead.x), static_cast<int>(vHead.y),
						DrawColor
					);
				}
			}

			int nTextOffset = 0;

			g_Draw.String(
				g_Fonts[EFonts::DEBUG].m_dwFont,
				static_cast<int>(vScreen.x), static_cast<int>(vScreen.y) + nTextOffset,
				DrawColor, TXT_CENTERXY,
				Utils::ConvertUtf8ToWide(pPlayer->GetPlayerName()).c_str()
			);

			nTextOffset += g_Fonts[EFonts::DEBUG].m_nTall;

			g_Draw.String(
				g_Fonts[EFonts::DEBUG].m_dwFont,
				static_cast<int>(vScreen.x), static_cast<int>(vScreen.y) + nTextOffset,
				DrawColor, TXT_CENTERXY,
				L"%d / %d", pPlayer->m_iHealth(), pPlayer->GetMaxHealth()
			);

			nTextOffset += g_Fonts[EFonts::DEBUG].m_nTall;

			if (pPlayer->InCond(TF_COND_ZOOMED))
			{
				g_Draw.String(
					g_Fonts[EFonts::DEBUG].m_dwFont,
					static_cast<int>(vScreen.x), static_cast<int>(vScreen.y) + nTextOffset,
					{ 255, 255, 0, 255 }, TXT_CENTERXY,
					L"ZOOM"
				);
			}
		}
	}
}