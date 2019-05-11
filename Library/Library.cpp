// Library.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "Library.h"

using namespace std;
VMT* eventsVMT;

template <typename interface>
interface* ModuleSystem::LoadInterface(LPCSTR name)
{
	auto GetInterface = reinterpret_cast<void* (*)(LPCSTR, int)>(CreateInterface);
	interface* pointer = reinterpret_cast<interface*>(GetInterface(name, 0));
	cout << "  [-] " << name << ": " << pointer << endl; 
	return pointer;
}

ModuleSystem::ModuleSystem(LPCSTR module)
{
	cout << "Module \""<< (this->module = module) <<"\" loaded with handle " 
		<< hex << (library = GetModuleHandle(module)) << endl; 
	CreateInterface = (uintptr_t) GetProcAddress(library, "CreateInterface");
	cout << " [+] CreateInterface: " << hex << CreateInterface << endl; 
	// Idk what this was for
	InterfaceList = *reinterpret_cast<InterfaceReg**>(GetAbsoluteAddress(CreateInterface, 3));
	/*for (InterfaceReg* current = InterfaceList; current; current = current->m_pNext)
		printf("\t%s => 0x%llx\n", current->m_pName, current->m_CreateFn());*/
	
}

ModuleSystem::~ModuleSystem()
{
	CloseHandle(library);
}

ClientLoader::ClientLoader() : ModuleSystem("client.dll")
{
	client = LoadInterface<CSource2Client>("Source2Client002");
	//for (ClientClass* current = client->GetAllClasses(); current; current = current->m_pNext) {
	//	printf("\t%s <> %s\n", current->m_pNetworkName, current->m_pClassName);
	//} // String -> "Searching for entities with class/target name containing substring: '%s'\n"
	//  sub_18011BFB0 + 44     48 8D 0D 05 89 4F + lea     rcx, aSearchingForEn; "Searching for entities with class/targe"...
	//	sub_18011BFB0 + 4B     FF 15 3F 19 43 01     call    cs : Msg
	//	sub_18011BFB0 + 51     48 8B 0D 70 1C 5A + mov     rcx, cs : g_CGameEntitySystem
	entities = *reinterpret_cast<CGameEntitySystem**>(GetAbsoluteAddress((uintptr_t)library + 0x11c001, 3));
	events = *reinterpret_cast<CGameEventManager**>(GetAbsoluteAddress(*vmt_slot(client, 13) + 0x2C, 3));
	cout << " [+] CGameEventManager: " << events << endl;
	cout << " [+] CEntitySystem: " << entities << endl;
	cout << endl;
	for (int EntityIndex = 0; EntityIndex <= 10; EntityIndex++)
		if (auto pEntity = entities->GetBaseEntity(EntityIndex)) {
			const char* EntityClass = pEntity->SchemaDynamicBinding()->bindingName;
			printf("[+] pEntity: %p , %i , %s\n", pEntity, EntityIndex, EntityClass);
		}
}

EngineLoader::EngineLoader() : ModuleSystem("engine2.dll")
{
	DWORD index = 0;
	client = LoadInterface<CEngineClient>("Source2EngineToClient001");
	//cout << "GetLocalPlayer: " << (*(FARPROC**)engine)[22] << endl;
	//cout << "RETURN: " << engine->GetLocalPlayer(&index, 0) << endl;
	//cout << "INDEX: " << index << endl;
	cout << endl;
}