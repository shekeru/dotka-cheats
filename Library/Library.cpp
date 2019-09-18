// Library.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "Library.h"
using namespace std;

template <typename Object>
Object* Library::LoadInterface(LPCSTR name)
{
	static int code = 0;
	auto pointer = (Object*) CreateInterface(name, &code);
	printf("CreateInterface(%s, %d) => 0x%p\n", name, code, 
		pointer); return pointer;
}

void Internal::GetInterfaces(){
	// Load First Class Interfaces
	sdk.engine = engine->LoadInterface<CEngineClient>("Source2EngineToClient001");
	sdk.client = client->LoadInterface<CSource2Client>("Source2Client002");
	sdk.fonts = mats->LoadInterface<CFontManager>("FontManager_001");
	sdk.panel = vgui->LoadInterface<IVPanel>("VGUI_Panel010");
	//for (ClientClass* current = client->GetAllClasses(); current; current = current->m_pNext) {
	//	printf("\t%s <> %s\n", current->m_pNetworkName, current->m_pClassName);
	//} // String -> "Searching for entities with class/target name containing substring: '%s'\n"
	//  sub_18011BFB0 + 44     48 8D 0D 05 89 4F + lea     rcx, aSearchingForEn; "Searching for entities with class/targe"...
	//	sub_18011BFB0 + 4B     FF 15 3F 19 43 01     call    cs : Msg
	//	sub_18011BFB0 + 51     48 8B 0D 70 1C 5A + mov     rcx, cs : g_CGameEntitySystem
	//entities = *reinterpret_cast<CGameEntitySystem**>(GetAbsoluteAddress(*vmt_slot(client, 3) + 0x296, 3));
	sdk.entity = resolve_addr<CGameEntitySystem*>(0x0, *vmt_slot(sdk.client, 25), 3);
	sdk.events = resolve_addr<CGameEventManager*>(0x2c, *vmt_slot(sdk.client, 13), 3);
	sdk.cmode = resolve_addr<IClientMode*>(0x0, *vmt_slot(sdk.client, 38), 3);
	//events = *reinterpret_cast<CGameEventManager**>(GetAbsoluteAddress(*vmt_slot(client, 13) + 0xCF, 3));
	//events = *reinterpret_cast<CGameEventManager**>(GetAbsoluteAddress(*vmt_slot(client, 4) + 0xDF, 3));
	cout << " [+] CGameEventManager: " << sdk.events << endl;
	cout << " [+] CGameEntitySystem: " << sdk.entity << endl;
	cout << " [+] ClientModeShared: " << sdk.cmode << endl;
	cout << endl;
}