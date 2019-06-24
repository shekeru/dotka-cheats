#pragma once
#include "Library.h"
#include <functional>
#include <algorithm>

namespace SDK {
	// C_DotaPlayer
	void PrepareUnitOrders(CDotaPlayer *ecx, DotaUnitOrder_t order, int targetIndex, Vector movePosition,
		int abilityIndex, PlayerOrderIssuer_t orderIssuer, CDotaBaseNPC *entity, bool queue,
		OrderQueueBehavior_t queueBehavior, bool showEffects);
	// CSource2Client
	void FrameStageNotify(CSource2Client* ecx, ClientFrameStage_t stage);
	// CGameEntitySystem
	CEntityInstance* OnRemoveEntity(CGameEntitySystem*, CEntityInstance*, CEntityHandle);
	CEntityInstance* OnEntityParentChanged(CGameEntitySystem*, CEntityInstance*, CEntityInstance*);
	CEntityInstance* OnAddEntity(CGameEntitySystem*, CEntityInstance*, CEntityHandle);
	// CGameEventSystem
	bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
	void PaintTraverse(IVPanel*, IVGuiPaintSurface*, VPANEL, bool, bool);
	// Load All Menu Hooks
	inline void LoadActiveHooks() {
		vmt.client->HookVM(FrameStageNotify, 29);
		vmt.events->HookVM(FireEventClientSide, 8);
		// Entity System
		vmt.entity->HookVM(OnRemoveEntity, 15);
		vmt.entity->HookVM(OnAddEntity, 14);
		vmt.entity->HookVM(OnEntityParentChanged, 13);
		// Misc
		vmt.panel->HookVM(PaintTraverse, 55);
	}
}; 
