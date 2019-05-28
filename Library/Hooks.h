#include "Modules.h"

namespace SDK {
	bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
	//bool FireEvent(CGameEventManager *thisptr, CGameEvent *event, bool dontBroadcast);
	//void* OnAddEntity(CEntityInstance*, CEntityHandle);
	inline void LoadActiveHooks() {
		sdk.events->HookVM(SDK::FireEventClientSide, 8);
	}
}; 