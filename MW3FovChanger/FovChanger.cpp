#include "FovChanger.h"
#include "MemAccess.h"
#include "processhook.h"
#include <iostream>

FovChanger::FovChanger()
{
}


FovChanger::~FovChanger()
{
}

void FovChanger::ChangeFOV_SP(const HANDLE hProc, float fov)
{
	if (!hProc) return;

	MessageBeep(MB_OK);

	DWORD fovmemaddress;
	DWORD iw5spmodule;

	iw5spmodule = processhook::GetModuleBaseAddress(hProc, "iw5sp.exe");

	if (!iw5spmodule) return;

	fovmemaddress = iw5spmodule + 0x185757C;

	while (memext::write(hProc, (LPVOID)fovmemaddress, &fov, sizeof(float))) Sleep(100);
}

void FovChanger::ChangeFOV_MP(const HANDLE hProc, float fov)
{
	if (!hProc) return;

	MessageBeep(MB_OK);

	DWORD fovmemaddress;
	DWORD iw5mpmodule;

	iw5mpmodule = processhook::GetModuleBaseAddress(hProc, "iw5mp.exe");

	if (!iw5mpmodule) return;

	fovmemaddress = iw5mpmodule + 0x55E8EC4;

	while (memext::write(hProc, (LPVOID)fovmemaddress, &fov, sizeof(float))) Sleep(100);
}
