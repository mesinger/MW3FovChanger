#include "FovChanger.h"
#include "processhook.h"
#include <iostream>

void fovchanger::ChangeFOV_SP(const HANDLE hProc, float fov)
{
	if (!hProc) return;

	DWORD fovmemaddress;
	DWORD iw5spmodule;

	iw5spmodule = processhook::GetModuleBaseAddress(hProc, L"iw5sp.exe");

	if (!iw5spmodule) return;

	fovmemaddress = iw5spmodule + 0x185757C;

	while (WriteProcessMemory(hProc, (LPVOID)fovmemaddress, &fov, sizeof(float), NULL)) Sleep(100);
}

void fovchanger::ChangeFOV_MP(const HANDLE hProc, float fov)
{
	if (!hProc) return;

	DWORD fovmemaddress;
	DWORD iw5mpmodule;

	iw5mpmodule = processhook::GetModuleBaseAddress(hProc, L"iw5mp.exe");

	if (!iw5mpmodule) return;

	fovmemaddress = iw5mpmodule + 0x55E8EC4;

	while (WriteProcessMemory(hProc, (LPVOID)fovmemaddress, &fov, sizeof(float), NULL)) Sleep(100);
}
