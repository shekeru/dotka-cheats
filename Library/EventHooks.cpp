#include "stdafx.h"
#include "Library.h"

typedef bool(*EventClientFn)(CGameEventManager*, CGameEvent *);
void EvaluatePlayerDeath(CGameEvent* event);
const char* messages[] = {
	"say I'm glad you tried, I'm sure you'll do better next time...",
	"say Maybe you should try not resorting to violence?",
	"say I fully support your efforts!"
}; time_t recent = time(nullptr);

using namespace std;

bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event) 
{
	if (!strcmp(event->GetName(), "dota_player_kill"))
		EvaluatePlayerDeath(event);
	return eventsVMT->GetOriginalMethod<EventClientFn>(8)(thisptr, event);
}

void DispatchDeathTaunt(bool inLocalTeam) 
{
	if (inLocalTeam || difftime(time(nullptr), recent) < 45)
		return; time(&recent); cout << "Player Taunted!" << endl;
	engine.client->ExecuteClientCmd(messages[rand() % 3]);
}

void EvaluatePlayerDeath(CGameEvent* event)
{
	CDotaPlayer* player = nullptr;
	int playerId = event->GetInt("victim_userid");
	cout << "Player Death Event: " << event << " ==> " << playerId << "\n";
	for (int EntityIndex = 0; EntityIndex <= client.entities->GetHighestEntityIndex(); EntityIndex++)
		if (player = (CDotaPlayer*) client.entities->GetBaseEntity(EntityIndex)) {
			auto typeName = player->SchemaDynamicBinding()->bindingName;
			if (strcmp(typeName, "C_DOTAPlayer"))
				continue;
			if (player->GetPlayerID() == playerId)
				break;
			if (EntityIndex > 100)
				goto invalid;
		} // Initial Printing
	cout << " [+] PlayerName: " << player->GetPlayerName() << endl;
	cout << " [+] InLocalTeam: " << boolalpha << player->InLocalTeam() << endl;
		DispatchDeathTaunt(player->InLocalTeam());	
invalid: 
	cout << endl;
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