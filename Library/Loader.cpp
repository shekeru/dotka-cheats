// Library.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "System.h"

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
	// CloseHandle(library);
	// No need to apparently?
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
	//entities = *reinterpret_cast<CGameEntitySystem**>(GetAbsoluteAddress(*vmt_slot(client, 3) + 0x296, 3));
	entity = *reinterpret_cast<CGameEntitySystem**>(GetAbsoluteAddress(*vmt_slot(client, 25), 3));
	//events = *reinterpret_cast<CGameEventManager**>(GetAbsoluteAddress(*vmt_slot(client, 13) + 0x2C, 3));
	//events = *reinterpret_cast<CGameEventManager**>(GetAbsoluteAddress(*vmt_slot(client, 13) + 0xCF, 3));
	events = *reinterpret_cast<CGameEventManager**>(GetAbsoluteAddress(*vmt_slot(client, 4) + 0xDF, 3));
	cout << " [+] CGameEventManager: " << events << endl;
	cout << " [+] CGameEntitySystem: " << entity << endl;
	cout << endl;
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

Internal::Internal()
{
	// Virtual Tables
	events = new VMT(client.events);
	//entity = new VMT(client.entity);
	// Function Swaps
	events->HookVM(SDK::FireEventClientSide, 8);
	//entity->HookVM(SDK::OnAddEntity, 17);
	// Apply
	events->ApplyVMT();
	//entity->ApplyVMT();
}

Internal::~Internal()
{
	// Reverse Table
	//events->ReleaseVMT();
	//entity->ReleaseVMT();
	// Deallocate
}

