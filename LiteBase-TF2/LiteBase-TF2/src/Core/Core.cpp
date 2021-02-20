#include "Core.h"

//std::ofstream File;
//
//void DumpTable(RecvTable *pTable, int nDepth)
//{
//	if (!pTable)
//		return;
//
//	const char *Types[7] = { "int", "float", "Vec3", "Vec2", "const char *", "Array", "void *" };
//
//	static std::string sClassName = pTable->GetName();
//	
//	if (nDepth == 0) {
//		sClassName = pTable->GetName();
//		sClassName.replace(0, 3, "C");
//	}
//
//	if (nDepth == 0)
//		File << "class " << sClassName << "\n{\npublic:\n";
//
//	for (int n = 0; n < pTable->m_nProps; n++)
//	{
//		RecvProp *pProp = pTable->GetPropW(n);
//
//		if (!pProp)
//			continue;
//
//		std::string_view sVarName(pProp->m_pVarName);
//
//		if (!sVarName.find("baseclass") || !sVarName.find("0") || !sVarName.find("1") || !sVarName.find("2"))
//			continue;
//
//		if (pProp->GetOffset())
//			File << "\tNETVAR(" << pProp->GetName() << ", " << Types[pProp->GetType()] << ", \"" << sClassName << "\", \"" << pProp->GetName() << "\");\n";
//
//		if (auto DataTable = pProp->GetDataTable())
//			DumpTable(DataTable, nDepth + 1);
//	}
//
//	if (nDepth == 0)
//		File << "};\n";
//}
//
//void DumpTables()
//{
//	File.open("NETVAR_DUMP.h");
//
//	for (ClientClass *pClass = g_pBaseClientDLL->GetAllClasses(); pClass; pClass = pClass->m_pNext)
//		DumpTable(pClass->m_pRecvTable, 0);
//
//	File.close();
//}

//void DumpClassIds()
//{
//	std::ofstream File("ClassIds.h");
//
//	File << "enum EClassIds" << "\n{\n";
//
//	for (auto pCurr = I::BaseClientDLL->GetAllClasses(); pCurr; pCurr = pCurr->m_pNext)
//		File << "\t" << pCurr->m_pNetworkName << " = " << pCurr->m_ClassID << ",\n";
//
//	File << "};";
//
//	File.close();
//}

void CCore::Load()
{
	while (!GetModuleHandleW(L"mss32.dll"))
		Sleep(2500); //https://youtu.be/Ny_HsSmiL9A?t=62

	//Interfaces
	{
		void *pClientTable = reinterpret_cast<void *>(g_Pattern.Find(L"client.dll", L"8B 0D ? ? ? ? 8B 02 D9 05"));
		I::Surface = reinterpret_cast<ISurface *>(g_Interface.Get(L"vguimatsurface.dll", "VGUI_Surface030"));
		I::EngineClient = reinterpret_cast<IVEngineClient013 *>(g_Interface.Get(L"engine.dll", "VEngineClient013"));
		I::BaseClientDLL = reinterpret_cast<IBaseClientDLL *>(g_Interface.Get(L"client.dll", "VClient017"));
		I::ClientEntityList = reinterpret_cast<IClientEntityList *>(g_Interface.Get(L"client.dll", "VClientEntityList003"));
		I::ModelInfo = reinterpret_cast<IVModelInfo *>(g_Interface.Get(L"engine.dll", "VModelInfoClient006"));
		I::DebugOverlay = reinterpret_cast<IVDebugOverlay *>(g_Interface.Get(L"engine.dll", "VDebugOverlay003"));
		I::ClientModeShared = **reinterpret_cast<CClientModeShared ***>(reinterpret_cast<DWORD>(pClientTable) + 0x2);
		I::MaterialSystem = reinterpret_cast<IMaterialSystem *>(g_Interface.Get(L"materialsystem.dll", "VMaterialSystem081"));
		I::ModelRender = reinterpret_cast<IVModelRender *>(g_Interface.Get(L"engine.dll", "VEngineModel016"));
		I::EngineVGui = reinterpret_cast<IEngineVGui *>(g_Interface.Get(L"engine.dll", "VEngineVGui001"));
		I::RenderView = reinterpret_cast<IVRenderView *>(g_Interface.Get(L"engine.dll", "VEngineRenderView014"));
		I::PlayerInfoManager = reinterpret_cast<IPlayerInfoManager *>(g_Interface.Get(L"server.dll", "PlayerInfoManager002"));
		I::GlobalVars = I::PlayerInfoManager->GetGlobalVars();
		I::EngineTrace = reinterpret_cast<IEngineTrace *>(g_Interface.Get(L"engine.dll", "EngineTraceClient003"));
		I::CVar = reinterpret_cast<ICvar *>(g_Interface.Get(L"vstdlib.dll", "VEngineCvar004"));
	}
	
	//Other
	{
		g_Draw.ReloadFonts();
		g_Draw.UpdateScreenSize();
	}

	//Hooks
	{
		MH_Initialize();
		{
			Hooks::WndProc::Init();
			Hooks::CreateMove::Init();
			Hooks::Paint::Init();
			Hooks::OnScreenSizeChanged::Init();
			Hooks::FrameStageNotify::Init();
			Hooks::LevelInitPreEntity::Init();
			Hooks::LevelInitPostEntity::Init();
			Hooks::LevelShutdown::Init();
			Hooks::DrawModelExecute::Init();
			Hooks::IsPlayerOnSteamFriendsList::Init();
		}
		MH_EnableHook(MH_ALL_HOOKS);
	}
}

void CCore::Unload()
{
	MH_Uninitialize();
	SetWindowLongPtr(Hooks::WndProc::hwWindow, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc::Original);
}

bool CCore::ShouldUnload()
{
	return GetAsyncKeyState(VK_F11) & 0x8000;
}