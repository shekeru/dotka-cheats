#pragma once
#include "sdk.h"

#define get_int(name) \
	int name = event->GetInt(#name); 
#define get_string(name) \
	const char* name = event->GetString(#name); 
#define get_float(name) \
	float name = event->GetFloat(#name); 

void DotaPlayerPickHero(CGameEvent* event);
// Uses Client PlayerIDs... what the fuck
#define dota_player_pick_hero_macro \
	get_int(player); /* Not ServerID, wtf */ \
	get_int(heroindex); /* eIndex of Hero */\
	get_string(hero); /* weird hero typename*/

void DotaPlayerKill(CGameEvent* event);
// Uses Client PlayerIDs... what the fuck
#define dota_player_kill_macro \
	get_int(victim_userid); /* Not ServerID, wtf */ \
	get_int(bounty); get_int(neutral); get_int(greevil); \
	get_int(killer1_userid); get_int(killer2_userid); \
	get_int(killer3_userid); get_int(killer4_userid); \
	get_int(killer5_userid); 