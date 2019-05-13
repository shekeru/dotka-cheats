// Library Headers
#include "CSource2Client.h"
#include "CEngineClient.h"
// Managers & Systems
#include "CEventManager.h"
#include "CEntitySystem.h"
// Object Headers
#include "CDotaPlayer.h"
// Misc Required
#include "vmt.h"

namespace SDK {
	//bool FireEvent(CGameEventManager *thisptr, CGameEvent *event, bool dontBroadcast);
	bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
	//void* OnAddEntity(CEntityInstance*, CEntityHandle);
}; 
