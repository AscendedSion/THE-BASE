#include "DrawModelExecute.h"

void __fastcall Hooks::DrawModelExecute::Func(void *ecx, void *edx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	Hook.CallOriginal<fn>()(ecx, edx, state, pInfo, pCustomBoneToWorld);
}

void Hooks::DrawModelExecute::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(I::ModelRender, 19));
	Hook.Create(FN, Func);
}