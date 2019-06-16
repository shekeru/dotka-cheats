#include "stdafx.h"
#include "CEntitySystem.h"
#include "hooks.h"

CEntityInstance* SDK::OnAddEntity(CGameEntitySystem* ecx, CEntityInstance* ptr, CEntityHandle index)
{
	const char * typeName = ptr->SchemaDynamicBinding()->bindingName;
	if (!strcmp(typeName, "C_DOTAPlayer")) {
		printf("Player <%x> %s, index: %d\n", ptr, typeName, index & 0x7FFF);
		if (sdk.engine->GetLocalPlayer() == (index & 0x7FFF)) {
			printf("\tWarning, New local player set from data above!\n");
				sdk.LocalPlayer = (CDotaPlayer*) ptr;
		}
	} else if (strstr(typeName, "DOTA_Unit_Hero")) {
		auto hero = (CDotaBaseNPC*) ptr; sdk.Heroes.insert(hero);
		printf("Hero %s, owner: %d, index: %d\n", typeName, hero->GetPlayerOwnerID(), index & 0x7FFF);
		printf("%p vs %p, %p\n", hero->GetPlayerOwner(), sdk.LocalPlayer, sdk.LocalHero);
		if (hero->GetPlayerOwner() == sdk.LocalPlayer) {
			printf("\tWarning, New local hero set from data above!\n");
				sdk.LocalHero = hero;
		}
	} else if (strstr(typeName, "C_DOTA_BaseNPC_Creep")) {
		sdk.Creeps.insert((CDotaBaseNPC*) ptr);
	}; return vmt.entity->GetOriginalMethod(OnAddEntity)(ecx, ptr, index);
}

CEntityInstance* SDK::OnRemoveEntity(CGameEntitySystem* ecx, CEntityInstance* ptr, CEntityHandle index)
{
	const char * typeName = ptr->SchemaDynamicBinding()->bindingName;
	if (strstr(typeName, "DOTA_Unit_Hero")) {
		printf("Removing <%x> %s, index: %d\n", ptr, typeName, index & 0x7FFF);
		sdk.Heroes.erase((CDotaBaseNPC*)ptr);
	} else if (strstr(typeName, "C_DOTA_BaseNPC_Creep")) {
		sdk.Creeps.erase((CDotaBaseNPC*) ptr);
	}; return vmt.entity->GetOriginalMethod(OnRemoveEntity)(ecx, ptr, index);
}

CEntityInstance* SDK::OnEntityParentChanged(CGameEntitySystem* ecx, CEntityInstance* x, CEntityInstance* y)
{
	printf("Parent Changed: %s ?? %s\n", x->SchemaDynamicBinding()->bindingName, y->SchemaDynamicBinding()->bindingName);
	return vmt.entity->GetOriginalMethod(OnEntityParentChanged)(ecx, x, y);
}
