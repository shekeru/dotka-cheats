#include "stdafx.h"
#include "System.h"

ClientLoader client;
EngineLoader engine;
Internal sdk;

void ThreadEntry(HMODULE hInstance)
{
	cout << "Thread Started <OK>, Handle Address: " << hInstance << "\n\n";
	client = ClientLoader(); engine = EngineLoader(); sdk = Internal();
	cout << "System Init Finished <OK>, " << "Now Running PostStartupLogic"
		<< "...\n\n"; while (ThreadIsRunning()) PostStartupLogic();
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