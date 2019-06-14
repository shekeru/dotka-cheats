#include <functional>
#include <algorithm>
#include "stdafx.h"
#include "events.h"
#include "hooks.h"
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

void DispatchDeathTaunt(bool inLocalTeam)
{
	using namespace std::chrono_literals;
	if (inLocalTeam || difftime(time(0), recent) < 45)
		return; recent = time(0);
	sdk.engine->ExecuteClientCmd(messages[rand() % 11]);
}

void DotaPlayerKill(CGameEvent* event)
{
	dota_player_kill_macro; 
	cout << "Player Death Event: " << event << " ==> userid: " << victim_userid << "\n";
	CDotaBaseNPC* hero = *find_if(begin(sdk.Heroes), end(sdk.Heroes), 
		[&](CDotaBaseNPC* xs)->bool{
		return xs->GetPlayerOwnerID() == victim_userid;
	}); if (!hero) return;
	cout << " [+] BindingName: " << hero->SchemaDynamicBinding()->bindingName
		<< " -> " << hero << endl;
	cout << " [+] PlayerOwner: " << victim_userid << " | " << hero->GetPlayerOwner()
		<< " ==> " << hero->GetPlayerOwnerID() << endl;
	CDotaPlayer* player = hero->GetPlayerOwner(); if (!player) return;
	cout << " [+] BindingName: " << player->SchemaDynamicBinding()->bindingName << endl;
	cout << " [+] PlayerName: " << player->GetPlayerName() << endl;
	cout << " [+] InLocalTeam: " << boolalpha << player->InLocalTeam() << endl;
	cout << " [+] Health: " << hero->GetHealth()
		<< " / " << hero->GetMaxHealth() << endl;
	cout << " [+] Mana: " << hero->GetMana() << " / "
		<< hero->GetMaxMana() << endl;
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
	cout << "FUCK the engine: " << hex << sdk.engine->GetLocalPlayer();
	cout << " ???? "<< hex << sdk.entity->GetBaseEntity(g_LocalIndex) << endl;
	//CDotaPlayer* localplayer = (CDotaPlayer*) sdk.entity->GetBaseEntity(localID);
	//	printf("LOCALPLAYER OR BUST: %x\n", localplayer);
	DispatchDeathTaunt(player->InLocalTeam());
invalid:
	cout << endl;
}

//for (int EntityIndex = 0; EntityIndex <= sdk.entity->GetHighestEntityIndex(); EntityIndex++)
//if (player = (CDotaPlayer*)sdk.entity->GetBaseEntity(EntityIndex)) {
//	auto typeName = player->SchemaDynamicBinding()->bindingName;
//	if (strcmp(typeName, "C_DOTAPlayer"))
//		continue;
//	if (player->GetPlayerID() == victim_userid)
//		break;
//	if (EntityIndex > 100)
//		goto invalid;
//} // Initial Printing

//for (int EntityIndex = 0; EntityIndex <= sdk.entity->GetHighestEntityIndex(); EntityIndex++)
//if (auto entity = sdk.entity->GetBaseEntity(EntityIndex))
//if (strstr(entity->SchemaDynamicBinding()->bindingName, "DOTA_Unit_Hero")) {
//	CDotaBaseNPC* hero = (CDotaBaseNPC*)entity;
//	if (hero->GetPlayerOwner() != player)
//		continue;