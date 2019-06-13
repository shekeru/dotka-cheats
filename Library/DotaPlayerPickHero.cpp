#include "stdafx.h"
#include "events.h"
#include "hooks.h"

void DotaPlayerPickHero(CGameEvent* event) 
{
	dota_player_pick_hero_macro;
	auto entity = (CDotaBaseNPC*) sdk.entity->GetBaseEntity(heroindex);
	//if (entity) {
	//	auto playerId = entity->GetPlayerOwnerID(); sdk.Heroes[playerId] = entity;
	//	printf("[HeroPicked] PlayerID %d: <%d> %s\n", playerId, heroindex, hero);
	//}
}