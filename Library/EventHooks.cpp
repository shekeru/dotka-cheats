#include "stdafx.h"
#include "Library.h"

typedef bool(*FireEventFn)(CGameEventManager*, CGameEvent *, bool);
typedef bool(*FireEventClientSideFn)(CGameEventManager*, CGameEvent *);

using namespace std;

bool FireEvent(CGameEventManager *thisptr, CGameEvent *event, bool opts) {
	if (!strcmp(event->GetName(), "dota_player_kill")) {
		cout << "Player death! " << event->GetInt("victim_userid") << endl;
		cout << "entity ID: " <<
			client.entities->GetBaseEntity(event->GetInt("victim_userid") + 1) 
			<< endl;
	}
	return eventsVMT->GetOriginalMethod<FireEventFn>(8)(thisptr, event, opts);
}

bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event) {
	printf("ClientEvent Fired! (%s)\n", event->GetName());
	return eventsVMT->GetOriginalMethod<FireEventClientSideFn>(9)(thisptr, event);
}