// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#include "targetver.h"
#pragma once
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN             
// Windows Header Files
#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
// reference additional headers your program requires here
void BindCrtHandlesToStdHandles(bool bindStdIn, bool bindStdOut, bool bindStdErr);
void ClearConsole(char fill);