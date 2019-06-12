#include "Modules.h"
#pragma once

namespace SDK {
	bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
	//void* OnAddEntity(CEntityInstance*, CEntityHandle);
	inline void LoadActiveHooks() {
		sdk.events->HookVM(FireEventClientSide, 8);
	}
}; 
