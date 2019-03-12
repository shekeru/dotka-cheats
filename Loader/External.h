#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <string>

using namespace std;

class InjectionManager
{
public:
	HANDLE hProcess;
	PROCESSENTRY32 pEntry;
	LPTHREAD_START_ROUTINE LibraryLoad;
	LPVOID lpFileRemote;
	BOOL AttachProcess(string procName);
	void LoadPath(string filePath);
	InjectionManager();
	~InjectionManager();
};
