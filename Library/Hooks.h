#pragma once
#include "Library.h"

namespace SDK {
	void PaintTraverse(IVPanel*, IVGuiPaintSurface*, VPANEL, bool, bool);
	bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
	//void FrameStageNotify(CSource2Client* thisptr, ClientFrameStage_t stage);
	//void* OnAddEntity(CEntityInstance*, CEntityHandle);
	inline void LoadActiveHooks() {
		vmt.events->HookVM(FireEventClientSide, 8);
		vmt.panel->HookVM(PaintTraverse, 55);
	}
}; 
