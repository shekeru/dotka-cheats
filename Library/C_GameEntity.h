#pragma once
#include "CEntityInstance.h"
#include "Datamap.h"

class C_GameEntity
{
public:
	virtual void* C_BaseAnimating__GetDataDescMap(void); //
	virtual Datamap* GetPredDescMap(void); // 28
	virtual void* unk_GetCollideable(void);
	virtual void* GetPredictionCopyable(void); // 3
};