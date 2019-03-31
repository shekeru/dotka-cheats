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
		Datamap* pred = victim->GetPredDescMap();
		cout << " [+] PreDescMap: " << pred << endl;
		cout << "  [-] MapLength: " << pred->numFields << endl;
		cout << " [+] PlayerName: " << victim->GetPlayerName() << endl;
		cout << " [+] CharacterName: " << victim->GetCharacterDisplayName() << endl;
		CDotaBaseNPC* hero = (CDotaBaseNPC*)victim;
		cout << " [+] CurrentMana: " << hero->GetMana() << endl;
		cout << " [+] GetMaxMana: " << hero->GetMaxMana() << endl;
		cout << " [+] BaseNPC VMT: " << hex << *(uintptr_t*)hero << endl;
		//cout << "\tName: " << victim->GetPlayerName() << endl;
		//cout << "\tName: " << victim->GetCharacterDisplayName() << endl;
		cout << endl;
	}
	return eventsVMT->GetOriginalMethod<EventClientFn>(8)(thisptr, event);
}