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
		auto x = *this->GetNetworkOrigin();
		auto y = *attacker->GetNetworkOrigin();
		return attacker->GetAttackRange() 
			>= (y - x).Length2D();
	}
	inline bool CanLastHit(CDotaBaseNPC* attacker) {
		return GetHealth() * GetBaseArmor() 
			<= attacker->GetDamageMin();
	}
	// Virtuals
	virtual void GetZChangeSpeed(); // 302, 
	virtual void GetBonusFlyHeight(); // 303, 
	virtual void ShouldDoFlyHeightVisual(); // 304, 
	virtual bool IsPortraitEntity(); // 305, 
	virtual int GetHealthPercent(void); // 306, ???
	virtual float GetHealthRegen(void); // 307, low
	virtual float GetMana(void); // 308, ok
	virtual float GetMaxMana(); // 309, ok
	virtual float GetManaRegen(); // 310, low
	virtual float BaseManaRegen(); // 311, why
	virtual float BonusManaRegen(); // 312, ditto
	virtual float IdealManaRegen(); // 313, high
	virtual float BaseHealthRegen(); // 314, correct
	virtual float BonusHealthRegen(); // 315, this too
	virtual float IdealHealthRegen(); // 316, i guess
	virtual int WantsHealthBarNumbers(); // 317, bool?
	virtual float GetAttackRange(); // 318, 
	virtual float GetBaseArmor(); // 319, 
	virtual float GetMoreArmor(); // 320, 
	virtual float GetMagicResist(); // 321, 
	virtual float n_322(); // 322, 
	virtual float n_323(); // 323, attack speed, inverse?
	virtual float BaseMoveSpeed(); // 324, 
	virtual float IdealMoveSpeed(); // 325, 
	virtual float RealMoveSpeed(); // 326, 
	virtual void LoadVoiceResources(); // 327, 
	virtual bool IsValidAbilityToCast(); // 328, 
	virtual void n_329(); // 329, 
	virtual void n_330(); // 330, 
	virtual bool IsDemon(); // 331, 
	virtual bool IsRoshan(); // 332, 
	virtual void ShouldForwardPurchaseRequest(); // 333, 
	virtual void IsZombie(); // 334, 
	virtual void GetPortraitActivityModifier(); // 335, 
	virtual void CanAcceptTargetToAttack(); // 336, 
	virtual void UpdateSelectionRing(); // 337, 
	virtual void OverrideSelectionPriority(); // 338, 
	virtual void UpdateBasedOnDormancy(); // 339, 
	virtual void CanBeSelected(); // 340, 
	virtual void GetEffectiveInvisibilityLevel(); // 341, 
	virtual void ComputeTranslucencyType(); // 342, 
	virtual void GetUnitLabel(); // 343, 
	virtual void GetChosenTarget(); // 344, 
	virtual int GetDamageMin(); // 345, 
	virtual int GetDamageMax(); // 346, 
	virtual float GetDamageBonus(); // 347, 
	virtual bool IsRooted(); // 348, 
	virtual void n_349(); // 349, 
	virtual void n_350(); // 350, 
	virtual bool IsDisarmed(); // 351, 
	virtual bool IsAttackImmune(); // 352, 
	virtual bool IsSilenced(); // 353, 
	virtual bool IsMuted(); // 354, 
	virtual bool IsStunned(); // 355, 
	virtual bool IsHexed(); // 356, 
	virtual bool IsInvisible(); // 357, 
	virtual bool IsInvulnerable(); // 358, 
	virtual bool IsMagicImmune(); // 359, 
	virtual bool NoUnitCollision(); // 360, 
	virtual bool ProvidesVision(); // 361, 
	virtual bool IsNightmared(); // 362, 
	virtual bool IsEvadeDisabled(); // 363, 
	virtual bool IsUnselectable(); // 364, 
	virtual bool IsSpeciallyDeniable(); // 365, 
	virtual bool IsFrozen(); // 366, 
	virtual bool IsCommandRestricted(); // 367, 
	virtual bool NotOnMinimap(); // 368, 
	virtual bool NotOnMinimapForEnemies(); // 369, 
	virtual bool IsLowAttackPriority(); // 370, 
	virtual bool NoHealthBar(); // 371, 
	virtual bool NoTeamMoveTo(); // 372, 
	virtual bool NoTeamSelect(); // 373, 
	virtual bool PassivesDisabled(); // 374, 
	virtual bool IsDominated(); // 375, 
	virtual bool IsBlind(); // 376, 
	virtual bool IsOutOfGame(); // 377, 
	virtual bool IsFakeAlly(); // 378, 
	virtual void n_379(); // 379, 
	virtual void OnStatesAdded(); // 380, 
	virtual void OnStatesRemoved(); // 381, 
	virtual void OnDebuffStateAdded(); // 382, 
	virtual void OnDebuffStateRemoved(); // 383, 
	virtual bool HasMovementCapability(); // 384, 
	virtual bool HasFlyingVision(); // 385, 
	virtual bool IsFlyingVisually(); // 386, 
	virtual bool IsInventoryEnabled(); // 387, 
	virtual void CalculateActivityModifiers(); // 388, #STR: "FCVAR_NEVER_AS_STRING",
	virtual void GetSoundSet(); // 389, 
	virtual void GetSelectionGroup(); // 390, 
	virtual void GainedModifier(); // 391, 
	virtual void LostModifier(); // 392, 
	virtual void IsIllusion(); // 393, 
	virtual void UnitStatsNeedsRefresh(); // 394, 
	virtual void GetSpeechPitchLevel(); // 395, 
	virtual void ShouldTranslateResponse(); // 396, 
	virtual void CanSpeak(); // 397, 
	virtual void UsesCustomSpeechOperatorStack(); // 398, 
	virtual void OnDying(); // 399, 
	virtual void OnDeath(); // 400, 
	virtual void OnAlive(); // 401, 
	virtual void AttachAmbientEffects(); // 402, 
	virtual void UpdateOnModelChange(); // 403, 
	virtual void OnUnitSelectedByLocalPlayer(); // 404, 
	virtual void ShouldPerformLean(); // 405, 
	virtual void UsesConstantGesture(); // 406, 
	virtual void GetConstantGestureWeight(); // 407, 
	virtual void GetConstantGestureCycle(); // 408, 
	virtual void GestureCycleComplete(); // 409, 
	virtual void ParsePortraitInfo(); // 410, #STR: ".vmdl", "default", "-herorecorder"
	virtual CDotaPlayer* GetPlayerOwner(); // 411, 
	virtual int GetPlayerOwnerID(); // 412, 
	virtual void HasModifiedAbilityParticleName(); // 413, 
	virtual void GetModifiedAbilityParticleName(); // 414, 
	virtual void n_415(); // 415, 
	virtual void n_416(); // 416, 
	virtual void GetAbilityLayout(); // 417, #STR: "Ability%d"
	virtual void IsModelIndexOriginalModel(); // 418, 
	virtual void n_419(); // 419, 
	virtual void UpdateAttributesForArcanaLevel(); // 420, 
	virtual void ApplyAdditionalPortraitParticles(); // 421, 
	virtual void n_422(); // 422, 
	virtual void BuildAttachedParticleFilter(); // 423, 
	virtual void OnAssetModifiersUpdated(); // 424, 
	virtual void n_425(); // 425, 
	virtual void UpdateNonCacheableWearableData(); // 426, 
	virtual void CreateDictionaries(); // 427, #STR: "%s_Items", "%s_Abilities"
	virtual void PopulateDictionaries(); // 428, 
	virtual void SharedLoadNPCData(); // 429, 
	virtual void ComputeOverriddenGeneratingItem(); // 430, 
	virtual void n_431(); // 431, 
	virtual void n_432(); // 432, ,  
};