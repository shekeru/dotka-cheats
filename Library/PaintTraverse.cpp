#include "stdafx.h"
#include "hooks.h"

void SDK::PaintTraverse(IVPanel* ecx, IVGuiPaintSurface* surface, VPANEL panel, 
	bool force_repaint, bool allow_force)
{
	// No Point in wasting cycles
	if (!sdk.engine->IsInGame())
		goto original;
	// Get Max, and something....
	if (!sdk.LocalHero) goto original;
	// Continue
	surface->PushMakeCurrent(panel, false);
	// Creeps
	for(auto entity : sdk.Creeps) {
		auto dmg = sdk.LocalHero->GetDamageMin();
		auto health = entity->GetHealth();
		if (health && health < dmg * 2) {
			entity->DrawEntityDebugOverlays(ENTITYHITBOXES); // White
			if (health < dmg) {
				entity->DrawEntityDebugOverlays(ABSBOX); // Green
			}
		}
	}; 
	// Heroes
	for (auto hero : sdk.Heroes) {
		if (!hero->InLocalTeam())
			hero->DrawEntityDebugOverlays(ENTITYATTACHMENTS);
	};  
	// Wards
	for (auto ward : sdk.Wards) {
		if (!ward->InLocalTeam())
			ward->DrawEntityDebugOverlays(ENTITYATTACHMENTS);
			ward->DrawEntityDebugOverlays(ENTITYHITBOXES);
	};
	// Resume
	surface->PopMakeCurrent(panel);
original:
	vmt.panel->GetOriginalMethod(PaintTraverse)(ecx, surface, panel, 
		force_repaint, allow_force);
}