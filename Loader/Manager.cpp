#include "Injection.h"
#include <thread>
#include <chrono>

BOOL InjectionManager::AttachProcess(string procName)
{
	HANDLE hSnapshot;
	// Open Toolhelp Snapshot
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		cerr << "[AttachProcess] Snapshot failed"
			<< endl; goto bad_attach;
	} // Find Matching Process
	if (!Process32First(hSnapshot, &pEntry)) {
		cout << "[AttachProcess] Bad first process"
			<< endl; goto bad_attach;
	} do {
		if (!strcmp(procName.c_str(), pEntry.szExeFile)) {
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pEntry.th32ProcessID);
			CloseHandle(hSnapshot); return TRUE;
		}
	} while (Process32Next(hSnapshot, &pEntry));
bad_attach:
	CloseHandle(hSnapshot);
	return FALSE;
}

void InjectionManager::LoadPath(string filePath)
{
	using namespace std::chrono_literals;
	// Get Active Dota 2 Game
	while (!AttachProcess("dota2.exe"))
		this_thread::sleep_for(1s);
	// Allocate Memory and Commit
	lpFileRemote = VirtualAllocEx(hProcess, NULL, 260, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProcess, lpFileRemote, filePath.c_str(), filePath.size(), 0);
	cout << "[LoadPath] Wrote " << filePath.size() << " bytes to " << lpFileRemote << endl;
	HANDLE remoteThread = CreateRemoteThread(hProcess, NULL, 0, LibraryLoad, lpFileRemote, 0, NULL);
	cout << "[LoadPath] Currently running thread " << remoteThread << endl;
	// Check on Thread
	if (remoteThread && WaitForSingleObject(remoteThread, 10000) == WAIT_OBJECT_0)
		cout << "[LoadPath] Successfully Injected!\n";
	else
		cerr << "[LoadPath] Shits failed!\n";
	cout << "[LoadPath] Decomitting memory... " << VirtualFreeEx(hProcess, lpFileRemote, 
		0, MEM_RELEASE) << endl; CloseHandle(remoteThread);
}

InjectionManager::InjectionManager()
{
	hProcess = INVALID_HANDLE_VALUE;
	pEntry.dwSize = sizeof(PROCESSENTRY32);
	LibraryLoad = (LPTHREAD_START_ROUTINE) GetProcAddress(
		GetModuleHandle("kernel32.dll"), "LoadLibraryA"
	); cout << "[Injector] LoadLibraryA found at " << LibraryLoad << endl;
}


InjectionManager::~InjectionManager()
{
	CloseHandle(hProcess);
}