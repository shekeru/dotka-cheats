#include "stdafx.h"
#include "Library.h"

typedef bool(*FireEventFn)(CGameEventManager*, CGameEvent *, bool);
typedef bool(*FireEventClientSideFn)(CGameEventManager*, CGameEvent *);

using namespace std;

bool FireEvent(CGameEventManager *thisptr, CGameEvent *event, bool opts) {
	if (!strcmp(event->GetName(), "dota_player_kill")) {
		int playerId = event->GetInt("victim_userid"); CDotaPlayer* victim =
			(CDotaPlayer*) client.entities->GetBaseEntity(playerId + 1);
		cout << "Player death! " << victim << endl;
		cout << " [+] Team: " << victim->C_BaseEntity__GetPlayerName() << endl;
		//cout << "\tName: " << victim->GetPlayerName() << endl;
		//cout << "\tName: " << victim->GetCharacterDisplayName() << endl;
	}
	return eventsVMT->GetOriginalMethod<FireEventFn>(8)(thisptr, event, opts);
}

bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event) {
	printf("ClientEvent Fired! (%s)\n", event->GetName());
	return eventsVMT->GetOriginalMethod<FireEventClientSideFn>(9)(thisptr, event);
}