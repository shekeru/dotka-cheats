#include "stdafx.h"
#include "hooks.h"

CEntityInstance* SDK::OnAddEntity(CGameEntitySystem* ecx, CEntityInstance* ptr, CEntityHandle index)
{
	const char * typeName = ptr->SchemaDynamicBinding()->bindingName;
	printf("Adding <%x> %s, index: %d\n", ptr, typeName, index & 0x7FFF);
	// Add To Hero Map
	if (strstr(typeName, "C_DOTA_Unit_Hero")) {
		auto npc = (CDotaBaseNPC*) ptr;
		sdk.Heroes[npc -> GetPlayerOwnerID()] = npc;
	} else if (strstr(typeName, "C_DOTA_BaseNPC_Creep")) {
		sdk.Creeps.insert((CDotaBaseNPC*) ptr);
	}; return vmt.entity->GetOriginalMethod(OnAddEntity)(ecx, ptr, index);
}

CEntityInstance* SDK::OnRemoveEntity(CGameEntitySystem* ecx, CEntityInstance* ptr, CEntityHandle index)
{
	const char * typeName = ptr->SchemaDynamicBinding()->bindingName;
	printf("Removing <%x> %s, index: %d\n", ptr, typeName, index & 0x7FFF);
	if (strstr(typeName, "C_DOTA_Unit_Hero")) {
		auto npc = (CDotaBaseNPC*) ptr;
		sdk.Heroes.erase(npc->GetPlayerOwnerID());
	}
	else if (strstr(typeName, "C_DOTA_BaseNPC_Creep")) {
		sdk.Creeps.erase((CDotaBaseNPC*) ptr);
	}; return vmt.entity->GetOriginalMethod(OnRemoveEntity)(ecx, ptr, index);
}