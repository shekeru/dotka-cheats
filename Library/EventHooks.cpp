#include "stdafx.h"
#include "Library.h"

typedef bool(*EventClientFn)(CGameEventManager*, CGameEvent *);

using namespace std;

bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event) {
	if (!strcmp(event->GetName(), "dota_player_kill")) {
		int playerId = event->GetInt("victim_userid"); auto victim = 
			(CDotaPlayer*) client.entities->GetBaseEntity(playerId + 1);
		cout << "Player Death Event: " << victim << endl;
		cout << " [+] BindingName: " << victim->SchemaDynamicBinding()->bindingName << endl;
		cout << " [+] PlayerName: " << victim->GetPlayerName() << endl;
		// try to find
		for (int EntityIndex = 0; EntityIndex <= client.entities->GetHighestEntityIndex(); EntityIndex++)
			if (auto entity = client.entities->GetBaseEntity(EntityIndex))
				if (strstr(entity->SchemaDynamicBinding()->bindingName, "DOTA_Unit_Hero")) {
					CDotaBaseNPC* hero = (CDotaBaseNPC*) entity;
					if (hero->GetPlayerOwnerID() != playerId)
						continue;
					cout << " [+] BindingName: " << hero->SchemaDynamicBinding()->bindingName << endl;
					Datamap* pred = hero->GetPredDescMap();
					cout << " [+] PreDescMap: " << pred << endl;
					cout << "  [-] MapLength: " << pred->numFields << endl;
					cout << " [+] Health: " << hero->C_BaseEntity__GetHealth()
						<< " / " << hero->C_BaseEntity__GetMaxHealth() << endl;
					cout << " [+] Mana: " << hero->GetMana() << " / " 
						<< hero->GetMaxMana() << endl;
					cout << " [+] PlayerOwner: " << victim << " | " << hero->GetPlayerOwner() 
						<< " ==> " << hero->GetPlayerOwnerID() << endl;
					cout << " [+] Is Same Team: " << hero->C_BaseEntity__InLocalTeam() << endl;
					cout << " [+] Damages: " << dec << hero->C_DOTA_BaseNPC__GetDamageMin()
						<< " - " << hero->C_DOTA_BaseNPC__GetDamageMax() << endl;
				}		
		//cout << "\tName: " << victim->GetPlayerName() << endl;
		//cout << "\tName: " << victim->GetCharacterDisplayName() << endl;
		cout << endl;
	}
	return eventsVMT->GetOriginalMethod<EventClientFn>(8)(thisptr, event);
}