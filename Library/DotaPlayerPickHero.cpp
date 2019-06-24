#include "stdafx.h"
#include "gameevents.h"
#include "hooks.h"

void DotaPlayerPickHero(CGameEvent* event) 
{
	dota_player_pick_hero_macro;
	auto entity = (CDotaBaseNPC*) sdk.entity->GetBaseEntity(heroindex);
	if (entity) {
		auto playerId = entity->GetPlayerOwnerID();
		printf("[HeroPicked] PlayerID %d: <%d> %s", playerId, heroindex, hero);
		if (playerId == sdk.LocalPlayer->GetPlayerID()) {
			printf(" ((LOCALHERO))"); sdk.LocalHero = entity;
		} printf("\n");
	}
}