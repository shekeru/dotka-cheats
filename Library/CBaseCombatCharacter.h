#include "CBaseFlex.h"
#pragma once

class CBaseCombatCharacter : public CBaseFlex
{
public:
	virtual void n_270(); // 270, 
	virtual void n_271(); // 271, 
	virtual void n_272(); // 272, 
	virtual void n_273(); // 273, 
	virtual void n_274(); // 274, 
	virtual void n_275(); // 275, 
	virtual void n_276(); // 276, 
	virtual void n_277(); // 277, 
	virtual void n_278(); // 278, 
	virtual void IsLookingTowardsEntity(); // 279, 
	virtual void IsLookingTowardsVector(); // 280, 
	virtual void IsEntityInFOV(); // 281, 
	virtual void IsVectorInFOV(); // 282, 
	virtual Vector* IsLineOfSightClear(void* C_BaseEntity, int LineOfSightCheckType); // 283, 
	virtual bool IsLineOfSightClear(Vector &out, void* C_BaseEntity, int LineOfSightCheckType); // 284, 
	virtual void OnFootstep(); // 285, 
	virtual void GetGroundSurface(); // 286, 
	virtual void GetFootstepSound(); // 287, 
	virtual void AreFootstepsAudible(); // 288, 
	virtual void IsFootstepAudible(); // 289, 
	virtual void GetFootstepRunThreshold(); // 290, 
	virtual void IsGhost(); // 291, 
	virtual void UpdateParticles(); // 292, 
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