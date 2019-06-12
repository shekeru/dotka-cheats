#pragma once
#include "CBaseModelEntity.h"

class CBaseAnimating : public CBaseModelEntity {
public:
	virtual void SetTransmit(); // 218, 
	virtual void GetRenderData(); // 219, 
	virtual void UpdateClientSideAnimation(); // 220, 
	virtual void ComputeClientSideAnimationFlags(); // 221, 
	virtual void n_222(); // 222, 
	virtual void n_223(); // 223, 
	virtual void n_224(); // 224, 
	virtual void n_225(); // 225, 
	virtual void InitPoseParameters(); // 226, 
	virtual void CachePoseParameters(); // 227, 
	virtual void UncorrectViewModelAttachment(); // 228, 
	virtual void SetModelScale(); // 229, 
	virtual void OnNewSequence(); // 230, 
	virtual void IsActivityFinished(); // 231, 
	virtual void OnSequenceFinished(); // 232, 
	virtual void GetIdealSpeed(); // 233, 
	virtual void GetIdealAccel(); // 234, 
	virtual void n_235(); // 235, 
	virtual void HandleAnimEvent(); // 236, 
	virtual void n_237(); // 237, 
	virtual void n_238(); // 238, #STR: "cl_particle_fallback_base", "attachment_type",
	virtual void HandleScriptedAnimEvent(); // 239, 
	virtual void HandleBehaviorAnimEvent(); // 240, 
	virtual void SpeechAnimEvent(); // 241, 
	virtual void ControlMouth(); // 242, #STR: "mouth"
	virtual void IsViewModelOrAttachment(); // 243, 
	virtual void n_244(); // 244, 
	virtual void IsClientRagdoll(); // 245, 
	virtual void BecomeRagdollOnClient(); // 246, 
	virtual void CreateClientRagdoll(); // 247, #STR: "client_ragdoll"
	virtual void GetRagdollInitBoneArrays(); // 248, 
	virtual void n_249(); // 249, 
	virtual void DispatchMuzzleEffect(); // 250, #STR: "attachment", "COMBINE", "PISTOL", "SHOTGUN", "weaponType"
	virtual void EjectParticleBrass(); // 251, 
	virtual void DoMuzzleFlash(); // 252, 
	virtual void ProcessMuzzleFlashEvent(); // 253, 
	virtual void IsViewModel(); // 254, 
	virtual void FormatViewModelAttachment(); // 255, 
	virtual void IsMenuModel(); // 256, 
	virtual void ComputeStencilState(); // 257, 
	virtual void WantsInterpolatedVars(); // 258, 
	virtual void n_259(); // 259, 
	virtual void n_260(); // 260, 
};

class CBaseAnimatingOverlay : public CBaseAnimating {
public:
	virtual void AnimatingOverlayFn(); // 261, anim overlay 
};

class CBaseFlex : public CBaseAnimatingOverlay {
public:
	virtual void InitPhonemeMappings(); // 262, #STR: "%s_weak", "%s_strong", "phonemes"
	virtual void OwnsChoreoScene(); // 263, 
	virtual void OverrideBlinkWeight(); // 264, 
	virtual void StartSceneEvent(); // 265, 
	virtual void ProcessSequenceSceneEvent(); // 266, 
	virtual void ClearSceneEvent(); // 267, 
	virtual void CheckSceneEventCompletion(); // 268, 
	virtual void ShouldProcessSceneEvents(); // 269, 
};