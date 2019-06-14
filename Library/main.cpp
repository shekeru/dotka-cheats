#include "stdafx.h"
#include "Hooks.h"

DWORD WINAPI ModuleEntry(HMODULE hInstance)
{
	// Debug Console
#ifdef _DEBUG
	Utils::EnableConsole();
#endif
	try {
		printf("DotkaLib, Handle Address: %x\n\n", hInstance);
		cheat.GetModules(); cheat.GetInterfaces(); vmt.CreateVMTs();
			SDK::LoadActiveHooks(); vmt.AttachVMs();
		printf("System Init Finished <OK>\n\n");
		// Wait for unload signal
		while (cheat.isRunning)
			Sleep(1000);
		// Remove Library
		vmt.UnloadAll();
		//cheat.Shutdown();
	}
	catch (const std::exception& ex) {
		printf("An error occured during initialization:\n");
		printf("%s\n", ex.what());
		printf("Press any key to exit.\n");
		Utils::ConsoleReadKey();
		Utils::DisableConsole();
	};
FreeLibrary:
	FreeLibraryAndExitThread(hInstance, 1);
	return 1;
}

BOOL WINAPI ModuleExit()
{
	// Debug Console
#ifdef _DEBUG
	Utils::DisableConsole();
#endif
	return TRUE;
}

BOOL APIENTRY DllMain(
	HMODULE hInstance,
	DWORD fdwReason,
	LPVOID lpvReserved
) {
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hInstance);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)
			ModuleEntry, hInstance, 0, 0); break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			return ModuleExit();
	// Might be useful?
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
	default:
		break;
    }
    return TRUE;
}