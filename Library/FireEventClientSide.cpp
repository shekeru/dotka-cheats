#include "stdafx.h"
#include "events.h"
#include "hooks.h"

bool SDK::FireEventClientSide(CGameEventManager *object, CGameEvent *event) 
{
	const char* eventName = event->GetName();
	if (!strcmp(eventName, "dota_player_pick_hero"))
		DotaPlayerPickHero(event);
	if (!strcmp(eventName, "dota_player_kill"))
		DotaPlayerKill(event);
	//if (!strcmp(eventName, "dota_player_update_assigned_hero"))
	//	printf("Assigned to player %d\n", event->GetInt("playerid"));
	if (!strcmp(eventName, "player_connect")) {
		printf("Player <%s> %d - %d (STEAM:%s) connected %s\n",
			event->GetString("name"),
			event->GetInt("index"), // entityIndex - 1?
			event->GetInt("userid"), // ServerID
			event->GetString("networkid"),
			event->GetString("address"));
	}
	if (!strcmp(eventName, "player_connect_full")) {
		printf("LocalPlayer %d - %d (PlayerID: %d) \n",
			event->GetInt("index"), // entityIndex - 1?
			event->GetInt("userid"), // ServerID
			event->GetInt("PlayerID"));
	}
	// Debug and Return
	if (strcmp(eventName, "dota_action_success") && false)
		printf("Event %s at %x for %x\n", eventName, event, object);
	return vmt.events->GetOriginalMethod(FireEventClientSide)(object, event);
}

//	cout << " [+] BindingName: " << typeName << endl;
//for (int EntityIndex = 0; EntityIndex <= client.entities->GetHighestEntityIndex(); EntityIndex++)
//	if (auto entity = client.entities->GetBaseEntity(EntityIndex))
//		if (strstr(entity->SchemaDynamicBinding()->bindingName, "DOTA_Unit_Hero")) {
//			CDotaBaseNPC* hero = (CDotaBaseNPC*) entity;
//			if (hero->GetPlayerOwnerID() != playerId)
//				continue;
//			//cout << " [+] BindingName: " << hero->SchemaDynamicBinding()->bindingName << endl;
//			//Datamap* pred = hero->GetPredDescMap();
//			//cout << " [+] PreDescMap: " << pred << endl;
//			//cout << "  [-] MapLength: " << pred->numFields << endl;
//			//cout << " [+] Health: " << hero->C_BaseEntity__GetHealth()
//			//	<< " / " << hero->C_BaseEntity__GetMaxHealth() << endl;
//			//cout << " [+] Mana: " << hero->GetMana() << " / " 
//			//	<< hero->GetMaxMana() << endl;
//			//cout << " [+] PlayerOwner: " << victim << " | " << hero->GetPlayerOwner() 
//			//	<< " ==> " << hero->GetPlayerOwnerID() << endl;
//			//cout << " [+] Is Same Team: " << hero->C_BaseEntity__InLocalTeam() << endl;
//			//cout << " [+] Damages: " << dec << hero->C_DOTA_BaseNPC__GetDamageMin()
//			//	<< " - " << hero->C_DOTA_BaseNPC__GetDamageMax() << endl;
//			if (!hero->C_BaseEntity__InLocalTeam()) {
//				engine.client->ExecuteClientCmd(message);
//				cout << "\t" << "TRIGGERED" << endl;
//			}
//		}	