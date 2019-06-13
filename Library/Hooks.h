#pragma once
#include "Library.h"

namespace SDK {
	void PaintTraverse(IVPanel*, IVGuiPaintSurface*, VPANEL, bool, bool);
	bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
	//void FrameStageNotify(CSource2Client* thisptr, ClientFrameStage_t stage);
	CEntityInstance* OnAddEntity(CGameEntitySystem*, CEntityInstance*, CEntityHandle);
	CEntityInstance* OnRemoveEntity(CGameEntitySystem*, CEntityInstance*, CEntityHandle);
	//void* OnAddEntity(CEntityInstance*, CEntityHandle);
	inline void LoadActiveHooks() {
		vmt.events->HookVM(FireEventClientSide, 8);
		vmt.entity->HookVM(OnAddEntity, 14);
		vmt.panel->HookVM(PaintTraverse, 55);
	}
}; 
