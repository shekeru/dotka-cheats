#pragma once
#include "Library.h"

namespace SDK {
	bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
	//void* OnAddEntity(CEntityInstance*, CEntityHandle);
	inline void LoadActiveHooks() {
		vmt.events->HookVM(FireEventClientSide, 8);
	}
}; 
