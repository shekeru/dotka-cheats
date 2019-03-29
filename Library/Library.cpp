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
	cout << "[" << module << "] Loaded symbol <" << name << "> at " 
		<< pointer << endl; return pointer;
}

ModuleSystem::ModuleSystem(LPCSTR module)
{
	cout << "["<<module<<"] Loaded with handle " << 
		(library = GetModuleHandle(module)) 
	<< endl; CreateInterface = (uintptr_t) GetProcAddress(library, "CreateInterface");
	cout << "["<<module<<"] CreateInterface found at " << hex << CreateInterface << endl; 
	InterfaceList = *reinterpret_cast<InterfaceReg**>(GetAbsoluteAddress(CreateInterface, 3));
	/*for (InterfaceReg* current = InterfaceList; current; current = current->m_pNext)
		printf("\t%s => 0x%llx\n", current->m_pName, current->m_CreateFn());*/
	this->module = module;
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
	cout << "[" << module << "] CEntitySystem found at " << entities << endl;
	//cout << "TYPE: " << test->GetBaseEntity(1)->Schema_DynamicBinding()->bindingName << endl;
	//cout << "HIGHEST: " << test->GetHighestEntityIndex() << endl;
	//for (int EntityIndex = 0; EntityIndex <= entities->GetHighestEntityIndex(); EntityIndex++)
	for (int EntityIndex = 0; EntityIndex <= 10; EntityIndex++)
		if (auto pEntity = entities->GetBaseEntity(EntityIndex)){
			const char* EntityClass = pEntity->Schema_DynamicBinding()->bindingName;
			printf("[+] pEntity: %p , %i , %s\n", pEntity, EntityIndex, EntityClass);
			cout << "Name: " << ((CDotaPlayer*)pEntity)->C_DOTAPlayer__GetPlayerName() << endl;
		} 
	// Shit
	events = *reinterpret_cast<CGameEventManager**>(GetAbsoluteAddress(*vmt_slot(client, 13) + 0x2C, 3));
	cout << "[" << module << "] CGameEventManager found at " << entities << endl;
}

EngineLoader::EngineLoader() : ModuleSystem("engine2.dll")
{
	DWORD index = 0;
	engine = LoadInterface<CEngineClient>("Source2EngineToClient001");
	//cout << "GetLocalPlayer: " << (*(FARPROC**)engine)[22] << endl;
	//cout << "RETURN: " << engine->GetLocalPlayer(&index, 0) << endl;
	//cout << "INDEX: " << index << endl;
}