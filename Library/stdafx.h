// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <ctime>
#include <io.h>
// reference additional headers your program requires here
void BindCrtHandlesToStdHandles(bool bindStdIn, bool bindStdOut, bool bindStdErr);
void ClearConsole(char fill);