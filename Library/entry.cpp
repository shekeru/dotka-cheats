#include <stdio.h>
#include "main.h"

DWORD WINAPI Thread(LPVOID lpvReserved)
{
  return NULL;
}

BOOL WINAPI DllMain(
  _In_ HINSTANCE hinstDLL,
  _In_ DWORD fdwReason,
  _In_ LPVOID lpvReserved
){
  if (fdwReason == DL_PROCESS_ATTACH)
    CreateThread(0, 0, Thread, lpvReserved, 0, 0);
  return True;
}
