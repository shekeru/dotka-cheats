#pragma once
#include "CBaseEntity.h"

class CBaseModelEntity : public CBaseEntity {
public:
	virtual void OnNewModel(); // 209, 
	virtual void GetColorModulation(); // 210, 
	virtual void GetGlobalFadeScale(); // 211, 
	virtual void DamageDecal(); // 212, 
	virtual void n_213(); // 213, 
	virtual void n_214(); // 214, 
	virtual void SetViewOffset(); // 215, 
	virtual void CanBeSeenByTeam(); // 216, 
	virtual void IsPartOfFOWSystem(); // 217, 
};
