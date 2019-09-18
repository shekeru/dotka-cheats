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
	virtual void nkb();
	virtual void nka();
	virtual void GetZChangeSpeed(); // 308, 
	virtual void GetBonusFlyHeight(); // 309, 
	virtual void ShouldDoFlyHeightVisual(); // 310, 
	virtual bool IsPortraitEntity(); // 311, 
	virtual int GetHealthPercent(void); // 312, ???
	virtual float GetHealthRegen(void); // 313, low
	virtual float GetMana(void); // 314, ok
	virtual float GetMaxMana(); // 315, ok
	virtual float GetManaRegen(); // 316, low
	virtual float BaseManaRegen(); // 317, why
	virtual float BonusManaRegen(); // 318, ditto
	virtual float IdealManaRegen(); // 319, high
	virtual float BaseHealthRegen(); // 320, correct
	virtual float BonusHealthRegen(); // 321, this too
	virtual float IdealHealthRegen(); // 322, i guess
	virtual int WantsHealthBarNumbers(); // 323, bool?
	virtual float GetAttackRange(); // 324, 
	virtual float GetBaseArmor(); // 325, 
	virtual float GetMoreArmor(); // 326, 
	virtual float GetMagicResist(); // 327, 
	virtual float n_328(); // 328, 
	virtual float n_329(); // 329, attack speed, inverse?
	virtual float BaseMoveSpeed(); // 330, 
	virtual float IdealMoveSpeed(); // 331, 
	virtual float RealMoveSpeed(); // 332, 
	virtual void LoadVoiceResources(); // 333, 
	virtual bool n_334(); // 334, 
	virtual void n_335(); // 335, 
	virtual void n_336(); // 336, 
	virtual bool IsDemon(); // 337, 
	virtual bool IsRoshan(); // 338, 
	virtual void ShouldForwardPurchaseRequest(); // 339, 
	virtual void IsZombie(); // 340, 
	virtual void GetPortraitActivityModifier(); // 341, 
	virtual void CanAcceptTargetToAttack(); // 342, 
	virtual void n_343(); // 343, 
	virtual void UpdateSelectionRing(); // 344, 
	virtual void OverrideSelectionPriority(); // 345, 
	virtual void UpdateBasedOnDormancy(); // 346, 
	virtual void CanBeSelected(); // 347, 
	virtual void GetEffectiveInvisibilityLevel(); // 348, 
	virtual void ComputeTranslucencyType(); // 349, 
	virtual void GetUnitLabel(); // 350, 
	virtual void GetChosenTarget(); // 351, 
	virtual int GetDamageMin(); // 352, 
	virtual int GetDamageMax(); // 353, 
	virtual float GetDamageBonus(); // 354, 
	virtual bool IsRooted(); // 355, 
	virtual void n_356(); // 356, 
	virtual void n_357(); // 357, 
	virtual bool IsDisarmed(); // 358, 
	virtual bool IsAttackImmune(); // 359, 
	virtual bool IsSilenced(); // 360, 
	virtual bool IsMuted(); // 361, 
	virtual bool IsStunned(); // 362, 
	virtual bool IsHexed(); // 363, 
	virtual bool IsInvisible(); // 364, 
	virtual bool IsInvulnerable(); // 365, 
	virtual bool IsMagicImmune(); // 366, 
	virtual bool NoUnitCollision(); // 367, 
	virtual bool ProvidesVision(); // 368, 
	virtual bool IsNightmared(); // 369, 
	virtual bool IsEvadeDisabled(); // 370, 
	virtual bool IsUnselectable(); // 371, 
	virtual bool IsSpeciallyDeniable(); // 372, 
	virtual bool IsFrozen(); // 373, 
	virtual bool IsCommandRestricted(); // 374, 
	virtual bool NotOnMinimap(); // 375, 
	virtual bool NotOnMinimapForEnemies(); // 376, 
	virtual bool IsLowAttackPriority(); // 377, 
	virtual bool NoHealthBar(); // 378, 
	virtual bool NoTeamMoveTo(); // 379, 
	virtual bool NoTeamSelect(); // 380, 
	virtual bool PassivesDisabled(); // 381, 
	virtual bool IsDominated(); // 382, 
	virtual bool IsBlind(); // 383, 
	virtual bool IsOutOfGame(); // 384, 
	virtual bool IsFakeAlly(); // 385, 
	virtual void OnStatesAdded(); // 386, 
	virtual void OnStatesRemoved(); // 387, 
	virtual void OnDebuffStateAdded(); // 388, 
	virtual void OnDebuffStateRemoved(); // 389, 
	virtual bool HasMovementCapability(); // 390, 
	virtual bool HasFlyingVision(); // 391, 
	virtual bool IsFlyingVisually(); // 392, 
	virtual bool IsInventoryEnabled(); // 393, 
	virtual void n_394(); // 394, 
	virtual void CalculateActivityModifiers(); // 395, #STR: "FCVAR_NEVER_AS_STRING",
	virtual void GetSoundSet(); // 396, 
	virtual void GetSelectionGroup(); // 397, 
	virtual void GainedModifier(); // 398, 
	virtual void LostModifier(); // 399, 
	virtual void IsIllusion(); // 400, 
	virtual void UnitStatsNeedsRefresh(); // 401, 
	virtual void GetSpeechPitchLevel(); // 402, 
	virtual void ShouldTranslateResponse(); // 403, 
	virtual void CanSpeak(); // 404, 
	virtual void UsesCustomSpeechOperatorStack(); // 405, 
	virtual void OnDying(); // 406, 
	virtual void OnDeath(); // 407, 
	virtual void OnAlive(); // 408, 
	virtual void AttachAmbientEffects(); // 409, 
	virtual void UpdateOnModelChange(); // 410, 
	virtual void OnUnitSelectedByLocalPlayer(); // 411, 
	virtual void ShouldPerformLean(); // 412, 
	virtual void UsesConstantGesture(); // 413, 
	virtual void GetConstantGestureWeight(); // 414, 
	virtual void GetConstantGestureCycle(); // 415, 
	virtual void GestureCycleComplete(); // 416, 
	virtual void ParsePortraitInfo(); // 417, #STR: ".vmdl", "default", "-herorecorder"
	virtual CDotaPlayer* GetPlayerOwner(); // 418, 
	virtual int GetPlayerOwnerID(); // 419, 
	virtual void HasModifiedAbilityParticleName(); // 420, 
	virtual void GetModifiedAbilityParticleName(); // 421, 
	virtual void n_422(); // 422, 
	virtual void n_423(); // 423, 
	virtual void GetAbilityLayout(); // 424, #STR: "Ability%d"
	virtual void IsModelIndexOriginalModel(); // 425, 
	virtual void n_426(); // 426, 
	virtual void UpdateAttributesForArcanaLevel(); // 427, 
	virtual void ApplyAdditionalPortraitParticles(); // 428, 
	virtual void n_429(); // 429, 
	virtual void BuildAttachedParticleFilter(); // 430, 
	virtual void OnAssetModifiersUpdated(); // 431, 
	virtual void n_432(); // 432, 
	virtual void UpdateNonCacheableWearableData(); // 433, 
	virtual void CreateDictionaries(); // 434, #STR: "%s_Items", "%s_Abilities"
	virtual void PopulateDictionaries(); // 435, 
	virtual void SharedLoadNPCData(); // 436, 
	virtual void ComputeOverriddenGeneratingItem(); // 437, 
	virtual void n_438(); // 438, 
	virtual void n_439(); // 439, 
	virtual void n_440(); // 440, 
};