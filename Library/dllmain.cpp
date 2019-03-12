// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

DWORD WINAPI ThreadEntry(LPVOID lpvReserved)
{
	MessageBox(NULL, TEXT("uwu"), TEXT("Thread Started"),
		MB_OK); return NULL;
}

BOOL APIENTRY DllMain(
	HMODULE hInstance,
	DWORD fdwReason,
	LPVOID lpvReserved
) {
	if (hInstance) 
		DisableThreadLibraryCalls(hInstance);
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
		if (!CreateThread(0, 0, ThreadEntry, lpvReserved, 0, 0)) {
			MessageBox(NULL, TEXT("idk lol"), TEXT("Thread Error"), 
				MB_OK | MB_ICONERROR); return FALSE;
		} else break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

