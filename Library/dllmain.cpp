// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Library.h"
using namespace std;

ClientLoader client;
EngineLoader engine;

void ThreadEntry(HMODULE hInstance)
{
	cout << "Thread Started <OK>, Handle Address: " << hInstance << "\n\n";
	ClientLoader client = ClientLoader(); EngineLoader engine = EngineLoader();
	// Event System VMT
	eventsVMT = new VMT(client.events); srand(time(nullptr));
	eventsVMT->HookVM(FireEventClientSide, 8); eventsVMT->ApplyVMT();
	// Finished 
	cout << "System Init Finished <OK>, Exiting Startup Thread...\n\n";
	//while (1) cycle_fuck();
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