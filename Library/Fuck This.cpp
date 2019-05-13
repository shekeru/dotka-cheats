#include "stdafx.h"
#include "System.h"
#include <thread>
#include <chrono>

typedef bool(*EventClientFn)(CGameEventManager*, CGameEvent *);
void EvaluatePlayerDeath(CGameEvent* event);

const char* messages[] = {
	"say Good game, well played.",
	"say I'm glad you tried, I'm sure you'll do better next time...",
	"say Maybe you should try not resorting to violence?",
	"say I fully support your efforts!",
	"say Please kindly fuck off",
	"say Boom! Headshot!",
	"say keep feeding",
	"say retard",
	"say lmao"
}; using namespace std;
time_t recent = time(nullptr);

bool SDK::FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event) 
{
	//if (!strcmp(event->GetName(), "dota_player_kill"))
		/*CreateThread(0, 0, (LPTHREAD_START_ROUTINE)
			EvaluatePlayerDeath, (LPVOID) event, 0, 0);*/
		//EvaluatePlayerDeath(event);
	cout << "Event " << event->GetName() << " at " << event << " for " 
		<< thisptr << endl;
	return sdk.events->GetOriginalMethod<EventClientFn>(8)(thisptr, event);
}

void DispatchDeathTaunt(bool inLocalTeam) 
{
	using namespace std::chrono_literals;
	if (inLocalTeam || difftime(time(nullptr), recent) < 45)
		return; recent = time(0); //this_thread::sleep_for(2s);
	engine.client->ExecuteClientCmd(messages[0]);
}

void EvaluatePlayerDeath(CGameEvent* event)
{
	CDotaPlayer* player = nullptr;
	int playerId = event->GetInt("victim_userid");
	cout << "Player Death Event: " << event << " ==> " << playerId << "\n";
	for (int EntityIndex = 0; EntityIndex <= client.entity->GetHighestEntityIndex(); EntityIndex++)
		if (player = (CDotaPlayer*) client.entity->GetBaseEntity(EntityIndex)) {
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