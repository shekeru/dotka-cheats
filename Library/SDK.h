#pragma once
#include "CSource2Client.h"
#include "CEngineClient.h"
#include "CEventManager.h"
#include "CEntitySystem.h"
#include "CDotaBaseNPC.h"
#include "CDotaPlayer.h"
#include "common.h"
#include "vmt.h"

bool FireEvent(CGameEventManager *thisptr, CGameEvent *event, bool dontBroadcast);
bool FireEventClientSide(CGameEventManager *thisptr, CGameEvent *event);
extern VMT* eventsVMT;