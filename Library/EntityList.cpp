#include "stdafx.h"
#include "hooks.h"

CEntityInstance* SDK::OnAddEntity(CGameEntitySystem* ecx, CEntityInstance* ptr, CEntityHandle index)
{
	const char * typeName = ptr->SchemaDynamicBinding()->bindingName;
	// Add To Hero Map
	if (strstr(typeName, "C_DOTA_Unit_Hero")) {
		printf("Adding <%x> %s, index: %d\n", ptr, typeName, index & 0x7FFF);
		sdk.Heroes.insert((CDotaBaseNPC*) ptr);
	} else if (strstr(typeName, "C_DOTA_BaseNPC_Creep")) {
		sdk.Creeps.insert((CDotaBaseNPC*) ptr);
	}; return vmt.entity->GetOriginalMethod(OnAddEntity)(ecx, ptr, index);
}

CEntityInstance* SDK::OnRemoveEntity(CGameEntitySystem* ecx, CEntityInstance* ptr, CEntityHandle index)
{
	const char * typeName = ptr->SchemaDynamicBinding()->bindingName;
	if (strstr(typeName, "C_DOTA_Unit_Hero")) {
		printf("Removing <%x> %s, index: %d\n", ptr, typeName, index & 0x7FFF);
		sdk.Heroes.erase((CDotaBaseNPC*)ptr);
	}
	else if (strstr(typeName, "C_DOTA_BaseNPC_Creep")) {
		sdk.Creeps.erase((CDotaBaseNPC*) ptr);
	}; return vmt.entity->GetOriginalMethod(OnRemoveEntity)(ecx, ptr, index);
}