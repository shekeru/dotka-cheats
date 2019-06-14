#include "stdafx.h"
#include "hooks.h"

CEntityInstance* SDK::OnAddEntity(CGameEntitySystem* ecx, CEntityInstance* ptr, CEntityHandle index)
{
	const char * typeName = ptr->SchemaDynamicBinding()->bindingName;
	if (!strcmp(typeName, "C_DOTAPlayer")) {
		printf("Player <%x> %s, index: %d\n", ptr, typeName, index & 0x7FFF);
		if (sdk.engine->GetLocalPlayer() == index & 0x7FFF)
			sdk.LocalPlayer = (CDotaPlayer*) ptr;
	} else if (strstr(typeName, "C_DOTA_Unit_Hero")) {
		printf("Hero <%x> %s, index: %d\n", ptr, typeName, index & 0x7FFF);
		auto new_hero = (CDotaBaseNPC*)ptr; sdk.Heroes.insert(new_hero);
		if (new_hero->GetPlayerOwner() == sdk.LocalPlayer)
			sdk.LocalHero = new_hero;
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
	} else if (strstr(typeName, "C_DOTA_BaseNPC_Creep")) {
		sdk.Creeps.erase((CDotaBaseNPC*) ptr);
	}; return vmt.entity->GetOriginalMethod(OnRemoveEntity)(ecx, ptr, index);
}