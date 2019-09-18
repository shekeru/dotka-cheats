#pragma once
#include "CBaseModelEntity.h"

class CBaseAnimating : public CBaseModelEntity {
public:
	virtual void SetTransmit(); // 221, 
	virtual void GetRenderData(); // 222, 
	virtual void UpdateClientSideAnimation(); // 223, 
	virtual void ComputeClientSideAnimationFlags(); // 224, 
	virtual void n_225(); // 225, 
	virtual void n_226(); // 226, 
	virtual void n_227(); // 227, 
	virtual void n_228(); // 228, 
	virtual void InitPoseParameters(); // 229, 
	virtual void CachePoseParameters(); // 230, 
	virtual void UncorrectViewModelAttachment(); // 231, 
	virtual void SetModelScale(); // 232, 
	virtual void OnNewSequence(); // 233, 
	virtual void IsActivityFinished(); // 234, 
	virtual void OnSequenceFinished(); // 235, 
	virtual void GetIdealSpeed(); // 236, 
	virtual void GetIdealAccel(); // 237, 
	virtual void n_238(); // 238, 
	virtual void HandleAnimEvent(); // 239, 
	virtual void n_240(); // 240, 
	virtual void n_241(); // 241, #STR: "cl_particle_fallback_base", "attachment_type",
	virtual void HandleScriptedAnimEvent(); // 242, 
	virtual void HandleBehaviorAnimEvent(); // 243, 
	virtual void SpeechAnimEvent(); // 244, 
	virtual void n_245(); // 245, 
	virtual void ControlMouth(); // 246, #STR: "mouth"
	virtual void IsViewModelOrAttachment(); // 247, 
	virtual void n_248(); // 248, 
	virtual void IsClientRagdoll(); // 249, 
	virtual void BecomeRagdollOnClient(); // 250, 
	virtual void CreateClientRagdoll(); // 251, #STR: "client_ragdoll"
	virtual void GetRagdollInitBoneArrays(); // 252, 
	virtual void n_253(); // 253, 
	virtual void DispatchMuzzleEffect(); // 254, #STR: "attachment", "COMBINE", "PISTOL", "SHOTGUN", "weaponType"
	virtual void EjectParticleBrass(); // 255, 
	virtual void DoMuzzleFlash(); // 256, 
	virtual void ProcessMuzzleFlashEvent(); // 257, 
	virtual void IsViewModel(); // 258, 
	virtual void FormatViewModelAttachment(); // 259, 
	virtual void IsMenuModel(); // 260, 
	virtual void ComputeStencilState(); // 261, 
	virtual void WantsInterpolatedVars(); // 262, 
	virtual void n_263(); // 263, 
	virtual void n_264(); // 264, 
};

class CBaseAnimatingOverlay : public CBaseAnimating {
public:
	virtual void AnimatingOverlayFn(); // 265, anim overlay 
};

class CBaseFlex : public CBaseAnimatingOverlay {
public:
	virtual void InitPhonemeMappings(); // 266, #STR: "%s_weak", "%s_strong", "phonemes"
	virtual void OwnsChoreoScene(); // 267, 
	virtual void OverrideBlinkWeight(); // 268, 
	virtual void StartSceneEvent(); // 269, 
	virtual void ProcessSequenceSceneEvent(); // 270, 
	virtual void ClearSceneEvent(); // 271, 
	virtual void CheckSceneEventCompletion(); // 272, 
	virtual void ShouldProcessSceneEvents(); // 273, 
};