#include "stdafx.h"
#include "hooks.h"

void old_code(IVGuiPaintSurface* surface);
void SDK::PaintTraverse(IVPanel* ecx, IVGuiPaintSurface* surface, VPANEL panel, 
	bool force_repaint, bool allow_force)
{
	surface->PushMakeCurrent(panel, false);
	// No Point in wasting cycles
	if (sdk.engine->IsInGame() && sdk.LocalHero)
		old_code(surface);
	// Continue
	int line = 45;
	auto display = [&](std::string text) {
		surface->DrawColoredText(HFont(2), 500, 
			line += 25, 255, 255, 255, 
			255, text.c_str());
	};
	for (auto hero : sdk.Heroes) {
		display(hero->SchemaDynamicBinding()->bindingName);
		//display(hero->CBE_PlayerName());
		if (!hero->InLocalTeam())
			hero->DrawEntityDebugOverlays(BBOX);
	};
	// Resume
	surface->PopMakeCurrent(panel);
original:
	vmt.panel->GetOriginalMethod(PaintTraverse)(ecx, surface, panel, 
		force_repaint, allow_force);
}

void old_code(IVGuiPaintSurface* surface)
{
	// Creeps
	for (auto entity : sdk.Creeps) {
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
			hero->DrawEntityDebugOverlays(BBOX);
	};
	// Wards
	for (auto ward : sdk.Wards) {
		if (!ward->InLocalTeam())
			ward->DrawEntityDebugOverlays(ENTITYATTACHMENTS);
		ward->DrawEntityDebugOverlays(ENTITYHITBOXES);
	};
}