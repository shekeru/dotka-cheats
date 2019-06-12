#include "stdafx.h"
#include "Hooks.h"
#include <thread>
#include <chrono>

const char* messages[] = {
	"say Good game, well played.",
	"say I'm glad you tried, I'm sure you'll do better next time...",
	"say Maybe you should try not resorting to violence?",
	"say I fully support your efforts!",
	"say Please kindly fuck off",
	"say Nice one mr. monkey.",
	"say Boom! Headshot!",
	"say keep feeding.",
	"say wanna yiff?",
	"say retard",
	"say lmao"
}; using namespace std;
time_t recent = time(nullptr);

void EvaluatePlayerDeath(CGameEvent* event);
bool SDK::FireEventClientSide(CGameEventManager *object, CGameEvent *event) 
{
	const char* eventName = event->GetName();
	if (!strcmp(eventName, "dota_player_kill"))
		EvaluatePlayerDeath(event);
	// Debug and Return
	//printf("Event %s at %x for %x\n", eventName, event, object);
	return vmt.events->GetOriginalMethod(FireEventClientSide)(object, event);
}

void DispatchDeathTaunt(bool inLocalTeam) 
{
	using namespace std::chrono_literals;
	if (inLocalTeam || difftime(time(0), recent) < 45)
		return; recent = time(0);
	sdk.engine->ExecuteClientCmd(messages[rand() % 11]);
}

void EvaluatePlayerDeath(CGameEvent* event)
{
	CDotaPlayer* player = nullptr; 
	int playerId = event->GetInt("victim_userid");
	cout << "Player Death Event: " << event << " ==> " << playerId << "\n";
	for (int EntityIndex = 0; EntityIndex <= sdk.entity->GetHighestEntityIndex(); EntityIndex++)
	if (player = (CDotaPlayer*) sdk.entity->GetBaseEntity(EntityIndex)) {
		auto typeName = player->SchemaDynamicBinding()->bindingName;
		if (strcmp(typeName, "C_DOTAPlayer"))
			continue;
		if (player->GetPlayerID() == playerId)
			break;
		if (EntityIndex > 100)
			goto invalid;
	} // Initial Printing
	cout << " [+] BindingName: " << player->SchemaDynamicBinding()->bindingName << endl;
	cout << " [+] PlayerName: " << player->GetPlayerName() << endl;
	cout << " [+] InLocalTeam: " << boolalpha << player->InLocalTeam() << endl;
		DispatchDeathTaunt(player->InLocalTeam());	

		for (int EntityIndex = 0; EntityIndex <= sdk.entity->GetHighestEntityIndex(); EntityIndex++)
		if (auto entity = sdk.entity->GetBaseEntity(EntityIndex))
			if (strstr(entity->SchemaDynamicBinding()->bindingName, "DOTA_Unit_Hero")) {
				CDotaBaseNPC* hero = (CDotaBaseNPC*) entity;
				cout << " [+] BindingName: " << hero->SchemaDynamicBinding()->bindingName << endl;
				cout << " [+] Health: " << hero->GetHealth()
					<< " / " << hero->GetMaxHealth() << endl;
				cout << " [+] Mana: " << hero->GetMana() << " / " 
					<< hero->GetMaxMana() << endl;
				cout << " [+] PlayerOwner: " << playerId << " | " << hero->GetPlayerOwner() 
					<< " ==> " << hero->GetPlayerOwnerID() << endl;
				cout << " [+] Is Same Team: " << hero->InLocalTeam() << endl;
				cout << " [+] Damages: " << dec << hero->GetDamageMin()
					<< " - " << hero->GetDamageMax() << endl;
				printf(" [+] HealthR: %f = %f + %f = %f\n", hero->GetHealthRegen(), hero->BaseHealthRegen(),
					hero->BonusHealthRegen(), hero->IdealHealthRegen());
				printf(" [+] ManaR: %f = %f + %f = %f\n", hero->GetManaRegen(), hero->BaseManaRegen(),
					hero->BonusManaRegen(), hero->IdealManaRegen());
				printf(" [+] Range, Base Armor, More Armor: %f | %f | %f \n", hero->GetAttackRange(), 
					hero->GetBaseArmor(), hero->GetMoreArmor());
				printf(" [+] Magic Resist: %f \n", hero->GetMagicResist());
				cout << " [+] 328/RMS: " << dec << hero->n_328() << " - " << hero->RealMoveSpeed() << endl;
			}	
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