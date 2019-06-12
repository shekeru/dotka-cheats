#include "stdafx.h"
#include "hooks.h"

void SDK::PaintTraverse(IVPanel* ecx, IVGuiPaintSurface* surface, VPANEL panel, 
	bool force_repaint, bool allow_force)
{
	static CBaseEntity* entity;	static int max;
	// No Point in wasting cycles
	if (!sdk.engine->IsInGame())
		goto original;
	// Get Max, and something....
	max = sdk.entity->GetHighestEntityIndex(); surface->PushMakeCurrent(panel, false);
	for (int i = 1; i <= max; i++) {
		if (!(entity = sdk.entity->GetBaseEntity(i)))
			continue;
		if (strstr(entity->SchemaDynamicBinding()->bindingName, "C_DOTA_BaseNPC_Creep")) {
			CDotaBaseNPC* creep = (CDotaBaseNPC*)entity;
			auto health = creep->GetHealth();
			if (health && health < 50) {
				entity->DrawEntityDebugOverlays(ENTITYHITBOXES); // White
				entity->DrawEntityDebugOverlays(ABSBOX); // Green
			}
		}
	}; surface->PopMakeCurrent(panel);
original:
	vmt.panel->GetOriginalMethod(PaintTraverse)(ecx, surface, panel, 
		force_repaint, allow_force);
}