#pragma once
#include "CBaseEntity.h"
#include "CBaseCombatCharacter.h"
class CDotaPlayer;
class C_DOTABaseAbility;
// xref "%s_Abilities" to CreateDictionaries() OR "-herorecorder" to ParsePortraitInfo
class CDotaBaseNPC : public CBaseCombatCharacter
{
public:
	inline bool IsInRange(CDotaBaseNPC* attacker) {
		if (!GetHealth()) return false;
		auto x = *this->GetNetworkOrigin();
		auto y = *attacker->GetNetworkOrigin();
		return attacker->GetAttackRange() 
			>= (y - x).Length2D();
	}
	inline bool CanLastHit(CDotaBaseNPC* attacker) {
		return GetHealth() <= attacker->GetDamageMin();
	}
	// Virtuals
	virtual void GetZChangeSpeed(); // 307, 
	virtual void GetBonusFlyHeight(); // 308, 
	virtual void ShouldDoFlyHeightVisual(); // 309, 
	virtual bool IsPortraitEntity(); // 310, 
	virtual int GetHealthPercent(void); // 311, ???
	virtual float GetHealthRegen(void); // 312, low
	virtual float GetMana(void); // 313, ok
	virtual float GetMaxMana(); // 314, ok
	virtual float GetManaRegen(); // 315, low
	virtual float BaseManaRegen(); // 316, why
	virtual float BonusManaRegen(); // 317, ditto
	virtual float IdealManaRegen(); // 318, high
	virtual float BaseHealthRegen(); // 319, correct
	virtual float BonusHealthRegen(); // 320, this too
	virtual float IdealHealthRegen(); // 321, i guess
	virtual int WantsHealthBarNumbers(); // 322, bool?
	virtual float GetAttackRange(); // 323, 
	virtual float GetBaseArmor(); // 324, 
	virtual float GetMoreArmor(); // 325, 
	virtual float GetMagicResist(); // 326, 
	virtual float n_327(); // 327, 
	virtual float n_328(); // 328, attack speed, inverse?
	virtual float BaseMoveSpeed(); // 329, 
	virtual float IdealMoveSpeed(); // 330, 
	virtual float RealMoveSpeed(); // 331, 
	virtual void LoadVoiceResources(); // 332, 
	virtual bool n_333(); // 333, 
	virtual void n_334(); // 334, 
	virtual void n_335(); // 335, 
	virtual bool IsDemon(); // 336, 
	virtual bool IsRoshan(); // 337, 
	virtual void ShouldForwardPurchaseRequest(); // 338, 
	virtual void IsZombie(); // 339, 
	virtual void GetPortraitActivityModifier(); // 340, 
	virtual void CanAcceptTargetToAttack(); // 341, 
	virtual void n_342(); // 342, 
	virtual void UpdateSelectionRing(); // 343, 
	virtual void OverrideSelectionPriority(); // 344, 
	virtual void UpdateBasedOnDormancy(); // 345, 
	virtual void CanBeSelected(); // 346, 
	virtual void GetEffectiveInvisibilityLevel(); // 347, 
	virtual void ComputeTranslucencyType(); // 348, 
	virtual void GetUnitLabel(); // 349, 
	virtual void GetChosenTarget(); // 350, 
	virtual int GetDamageMin(); // 351, 
	virtual int GetDamageMax(); // 352, 
	virtual float GetDamageBonus(); // 353, 
	virtual bool IsRooted(); // 354, 
	virtual void n_355(); // 355, 
	virtual void n_356(); // 356, 
	virtual bool IsDisarmed(); // 357, 
	virtual bool IsAttackImmune(); // 358, 
	virtual bool IsSilenced(); // 359, 
	virtual bool IsMuted(); // 360, 
	virtual bool IsStunned(); // 361, 
	virtual bool IsHexed(); // 362, 
	virtual bool IsInvisible(); // 363, 
	virtual bool IsInvulnerable(); // 364, 
	virtual bool IsMagicImmune(); // 365, 
	virtual bool NoUnitCollision(); // 366, 
	virtual bool ProvidesVision(); // 367, 
	virtual bool IsNightmared(); // 368, 
	virtual bool IsEvadeDisabled(); // 369, 
	virtual bool IsUnselectable(); // 370, 
	virtual bool IsSpeciallyDeniable(); // 371, 
	virtual bool IsFrozen(); // 372, 
	virtual bool IsCommandRestricted(); // 373, 
	virtual bool NotOnMinimap(); // 374, 
	virtual bool NotOnMinimapForEnemies(); // 375, 
	virtual bool IsLowAttackPriority(); // 376, 
	virtual bool NoHealthBar(); // 377, 
	virtual bool NoTeamMoveTo(); // 378, 
	virtual bool NoTeamSelect(); // 379, 
	virtual bool PassivesDisabled(); // 380, 
	virtual bool IsDominated(); // 381, 
	virtual bool IsBlind(); // 382, 
	virtual bool IsOutOfGame(); // 383, 
	virtual bool IsFakeAlly(); // 384, 
	virtual void OnStatesAdded(); // 385, 
	virtual void OnStatesRemoved(); // 386, 
	virtual void OnDebuffStateAdded(); // 387, 
	virtual void OnDebuffStateRemoved(); // 388, 
	virtual bool HasMovementCapability(); // 389, 
	virtual bool HasFlyingVision(); // 390, 
	virtual bool IsFlyingVisually(); // 391, 
	virtual bool IsInventoryEnabled(); // 392, 
	virtual void CalculateActivityModifiers(); // 393, #STR: "FCVAR_NEVER_AS_STRING",
	virtual void GetSoundSet(); // 394, 
	virtual void GetSelectionGroup(); // 395, 
	virtual void GainedModifier(); // 396, 
	virtual void LostModifier(); // 397, 
	virtual void IsIllusion(); // 398, 
	virtual void UnitStatsNeedsRefresh(); // 399, 
	virtual void GetSpeechPitchLevel(); // 400, 
	virtual void ShouldTranslateResponse(); // 401, 
	virtual void CanSpeak(); // 402, 
	virtual void UsesCustomSpeechOperatorStack(); // 403, 
	virtual void OnDying(); // 404, 
	virtual void OnDeath(); // 405, 
	virtual void OnAlive(); // 406, 
	virtual void AttachAmbientEffects(); // 407, 
	virtual void UpdateOnModelChange(); // 408, 
	virtual void OnUnitSelectedByLocalPlayer(); // 409, 
	virtual void ShouldPerformLean(); // 410, 
	virtual void UsesConstantGesture(); // 411, 
	virtual void GetConstantGestureWeight(); // 412, 
	virtual void GetConstantGestureCycle(); // 413, 
	virtual void GestureCycleComplete(); // 414, 
	virtual void ParsePortraitInfo(); // 415, #STR: ".vmdl", "default", "-herorecorder"
	virtual CDotaPlayer* GetPlayerOwner(); // 416, 
	virtual int GetPlayerOwnerID(); // 417, 
	virtual void HasModifiedAbilityParticleName(); // 418, 
	virtual void GetModifiedAbilityParticleName(); // 419, 
	virtual void n_420(); // 420, 
	virtual void n_421(); // 421, 
	virtual void GetAbilityLayout(); // 422, #STR: "Ability%d"
	virtual void IsModelIndexOriginalModel(); // 423, 
	virtual void n_424(); // 424, 
	virtual void UpdateAttributesForArcanaLevel(); // 425, 
	virtual void ApplyAdditionalPortraitParticles(); // 426, 
	virtual void n_427(); // 427, 
	virtual void BuildAttachedParticleFilter(); // 428, 
	virtual void OnAssetModifiersUpdated(); // 429, 
	virtual void n_430(); // 430, 
	virtual void UpdateNonCacheableWearableData(); // 431, 
	virtual void CreateDictionaries(); // 432, #STR: "%s_Items", "%s_Abilities"
	virtual void PopulateDictionaries(); // 433, 
	virtual void SharedLoadNPCData(); // 434, 
	virtual void ComputeOverriddenGeneratingItem(); // 435, 
	virtual void n_436(); // 436, 
	virtual void n_437(); // 437, 
	virtual void n_438(); // 438, 
};