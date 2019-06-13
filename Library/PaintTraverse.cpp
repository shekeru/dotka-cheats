#include "stdafx.h"
#include "hooks.h"

void SDK::PaintTraverse(IVPanel* ecx, IVGuiPaintSurface* surface, VPANEL panel, 
	bool force_repaint, bool allow_force)
{
	// No Point in wasting cycles
	if (!sdk.engine->IsInGame())
		goto original;
	// Get Max, and something....
	surface->PushMakeCurrent(panel, false);
	for(auto entity : sdk.Creeps) {
		if (!entity) continue;
		auto health = entity->GetHealth();
		if (health && health < 95) {
			entity->DrawEntityDebugOverlays(ENTITYHITBOXES); // White
			if (health < 65) {
				entity->DrawEntityDebugOverlays(ABSBOX); // Green
			}
		}
	}; surface->PopMakeCurrent(panel);
original:
	vmt.panel->GetOriginalMethod(PaintTraverse)(ecx, surface, panel, 
		force_repaint, allow_force);
}