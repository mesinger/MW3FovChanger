#include "processhook.h"
#include <Psapi.h>
#include <iostream>

UINT processhook::GetProcessId(const char * wndname)
{
	HWND hwind = FindWindowA(NULL, wndname);

	if (!hwind) return 0;

	DWORD pid;
	GetWindowThreadProcessId(hwind, &pid);

	return pid;
}

HANDLE processhook::ConnectToProcess(DWORD pid)
{
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
}

DWORD processhook::GetModuleBaseAddress(const HANDLE& hProc, const char * modulename)
{
	/*Get List of loaded modules in hProc*/

	HMODULE modules[1024];
	DWORD cmodules;

	if (!EnumProcessModulesEx(hProc, modules, sizeof(modules), &cmodules, LIST_MODULES_ALL)) return 0;

	cmodules /= sizeof(HMODULE);

	/*Iterate through modules and get base address*/

	char sbuf[128];
	MODULEINFO moduleInfo;
	moduleInfo.lpBaseOfDll = 0;

	for (int i = 0; i < cmodules; i++) {

		GetModuleBaseName(hProc, modules[i], sbuf, 128);

		if (strcmp(sbuf, modulename) == 0)
			GetModuleInformation(hProc, modules[i], &moduleInfo, sizeof(MODULEINFO));
	}

	return (DWORD)moduleInfo.lpBaseOfDll;
}