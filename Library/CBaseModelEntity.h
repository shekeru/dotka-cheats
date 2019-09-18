#pragma once
#include "CBaseEntity.h"

class CBaseModelEntity : public CBaseEntity {
public:
	virtual void OnNewModel(); // 212, 
	virtual void GetColorModulation(); // 213, 
	virtual void GetGlobalFadeScale(); // 214, 
	virtual void DamageDecal(); // 215, #STR: "ManhackCut", "BulletProof"
	virtual void n_216(); // 216, 
	virtual void n_217(); // 217, 
	virtual void SetViewOffset(); // 218, 
	virtual void CanBeSeenByTeam(); // 219, 
	virtual void IsPartOfFOWSystem(); // 220,  
};
