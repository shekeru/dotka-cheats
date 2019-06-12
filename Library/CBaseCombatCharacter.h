#pragma once
#include "CBaseFlex.h"

class CBaseCombatCharacter : public CBaseFlex
{
public:
	virtual void IsLookingTowardsEntity(); // 270, 
	virtual void IsLookingTowardsVector(); // 271, 
	virtual void IsEntityInFOV(CBaseEntity const&); // 272, 
	virtual void IsVectorInFOV(Vector const&); // 273, 
	virtual void n_274(); // 274, 
	virtual void n_275(); // 275, 
	virtual void n_276(); // 276, 
	virtual void n_277(); // 277, 
	virtual void n_278(); // 278, 
	virtual void n_279(); // 279, 
	virtual void OnFootstep(); // 280, 
	virtual void GetGroundSurface(); // 281, 
	virtual void GetFootstepSound(); // 282, 
	virtual void AreFootstepsAudible(); // 283, 
	virtual void IsFootstepAudible(); // 284, 
	virtual void GetFootstepRunThreshold(); // 285, 
	virtual void IsGhost(); // 286, 
	virtual void UpdateParticles(); // 287, 
	virtual void n_288(); // 288, 
	virtual void n_289(); // 289, 
	virtual void n_290(); // 290, 
	virtual void n_291(); // 291, 
	virtual void n_292(); // 292, 
	virtual void Weapon_OwnsThisType(); // 293, 
	virtual void n_294(); // 294, 
	virtual void Weapon_Switch(); // 295, 
	virtual void Weapon_CanSwitchTo(); // 296, 
	virtual void n_297(); // 297, 
	virtual void GetActiveWeapon(); // 298, 
	virtual void GetWeapon(int); // 299, 
	virtual void OnAmmoCountChanged(); // 300, 
	virtual void OnWearablesChanged(); // 301, 
};