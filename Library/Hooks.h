#pragma once
#include "Library.h"
#include <functional>
#include <algorithm>

namespace SDK {
	void PaintTraverse(IVPanel*, IVGuiPaintSurface*, VPANEL, bool, bool);
	bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
	void FrameStageNotify(CSource2Client* ecx, ClientFrameStage_t stage);
	CEntityInstance* OnAddEntity(CGameEntitySystem*, CEntityInstance*, CEntityHandle);
	CEntityInstance* OnRemoveEntity(CGameEntitySystem*, CEntityInstance*, CEntityHandle);
	//void* OnAddEntity(CEntityInstance*, CEntityHandle);
	inline void LoadActiveHooks() {
		vmt.client->HookVM(FrameStageNotify, 29);
		vmt.events->HookVM(FireEventClientSide, 8);
		// Entity System
		vmt.entity->HookVM(OnRemoveEntity, 15);
		vmt.entity->HookVM(OnAddEntity, 14);
		// Misc
		vmt.panel->HookVM(PaintTraverse, 55);
	}
}; 
