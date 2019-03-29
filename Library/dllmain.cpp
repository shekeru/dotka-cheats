// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Library.h"
using namespace std;

ClientLoader client;
EngineLoader engine;

void ThreadEntry(HMODULE hInstance)
{
	cout << "[Dotka Library] Injection <OK>, Handle <" << hInstance << ">\n";
	ClientLoader client = ClientLoader(); EngineLoader engine = EngineLoader();
	// Event System VMT
	eventsVMT = new VMT(client.events); eventsVMT->HookVM(FireEvent, 8);
	eventsVMT->HookVM(FireEventClientSide, 9); eventsVMT->ApplyVMT();
	// Finished
	cout << "[Dotka Library] Routines <OK>, Exiting...\n";
}

BOOL APIENTRY DllMain(
	HMODULE hInstance,
	DWORD fdwReason,
	LPVOID lpvReserved
) {
	AllocConsole(); 
	DisableThreadLibraryCalls(hInstance);
	BindCrtHandlesToStdHandles(true, true, true); 
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)
			ThreadEntry, hInstance, 0, 0); break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}