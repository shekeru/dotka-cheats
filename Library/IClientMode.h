#pragma once
#include "CBaseEntity.h"
#include "InputSystem.h"

// ClientModeShared
/* xref "dota_chat_ban_notification" to get to ClientModeDOTANormal::CanVoiceChat() */
class IClientMode
{
public:
	virtual void DESTROY(void) = 0; // 0
	virtual void InitViewport(void) = 0;
	virtual void Init(int CSplitScreenSlot) = 0; // 2
	virtual void VGUIShutdown(void) = 0;
	virtual void Shutdown(void) = 0; // 4
	virtual void GameShutdown();
	virtual void GameActivate(void) = 0;
	virtual void GameDeactivate(void) = 0;
	virtual void n_8() = 0; // 8
	virtual void n_9() = 0;
	virtual void n_10() = 0; // 10
	virtual void n_11() = 0;
	virtual bool ShouldDrawDetailObjects(void) = 0; // 12
	virtual bool ShouldDrawEntity(CBaseEntity *) = 0;
	virtual bool ShouldDrawLocalPlayer(CBaseEntity *) = 0; // 14
	virtual bool ShouldDrawParticles(void) = 0;
	virtual bool ShouldDrawFog(void) = 0;
	virtual void OverrideView(void *CViewSetup) = 0; // 17
	virtual void OverrideRenderBounds(int &, int &, int &, int &, int &, int &) = 0;
	virtual void OverrideAudioState(void* audioState_t) = 0;
	virtual void KeyInput(int, int buttonCode_t, const char*) = 0; // 20
	virtual void GetSlotForKeyInput(void) = 0;
	virtual void StartMessageMode(int) = 0; // 22
	virtual void sub_2DC5F20() = 0;
	virtual void sub_2DC4A00() = 0;
	virtual void OverrideMouseInput(float *, float *) = 0; //25
	virtual void OverrideJoystickInput(float *, float *) = 0;
	virtual bool CreateMove(void* thisptr, CUserCmd* user_cmd, void* a3, void* a4) = 0; // 27

	virtual void LevelInit(const char*) = 0;
	virtual void LevelShutdown(void) = 0;
	virtual bool ShouldDrawViewModel(void) = 0;
	virtual bool ShouldDrawCrosshair(void) = 0;
	virtual void PreRender(void *CViewSetup) = 0;
	virtual void PostRenderVGui(void) = 0;
	virtual void DoPostScreenSpaceEffects(void const * CViewSetup) = 0;
	virtual void ActivateInGameVguiContext(void *vguiPanel) = 0;
	virtual void DeactivateInGameVGuiContext(void) = 0;
	virtual float GetViewModelFOV(void) = 0;
	virtual bool CanRecordDemo(void) = 0;
	virtual void OnColorCorrectionWeightsReset(void) = 0;
	virtual void OnRemoveColorCorrectionEntity(void* CColorCorrection) = 0;
	virtual void GetColorCorrectionScale(void) = 0;
	virtual void OnResetHUD(void) = 0;
	virtual void HudElementKeyInput(int, int buttonCode_t, const char*) = 0;
	virtual void GetPropGlowColor(CBaseEntity const *) = 0;
	virtual int GetSplitScreenPlayerSlot(void) = 0;
	virtual void GetInputCommandSource(void) = 0;
	virtual bool CanVoiceChat(void) = 0;
	virtual const char* GetLoadingScreenImageName(char *argArr, int sizeOfArr, const char *) = 0;
	virtual void sub_2DE8160() = 0;
	virtual void sub_2DE8170() = 0;
	virtual void sub_2DC5E80() = 0;
	virtual void SetBlurFade(float) = 0;
	virtual float GetBlurFade(void) = 0;
	virtual void ClearBlurFade(void) = 0;
	virtual void OnLevelLoadingStarted(void) = 0;
	virtual void ReloadScheme(void) = 0;
	virtual void ReloadSchemeWithRoot(unsigned long long) = 0;
	virtual void FireGameEvent(void *IGameEvent) = 0;
	virtual void HandleSpectatorKeyInput(int, int buttonCode_t, const char *) = 0;
	virtual void InitChatHudElement(void) = 0;
	virtual void InitWeaponSelectionHudElement(void) = 0;
	virtual void InitCursors(void) = 0;
};
