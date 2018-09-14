#include "FovChanger.h"
#include "processhook.h"
#include <iostream>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <string>
#include <sstream>

fov::Changer::Changer(float fov)
	:fov(fov)
{
}

void fov::Changer::setfov_sp(const HANDLE hProc) const
{
	if (!hProc) return;

	DWORD fovmemaddress;
	DWORD iw5spmodule;

	iw5spmodule = processhook::GetModuleBaseAddress(hProc, L"iw5sp.exe");

	if (!iw5spmodule) return;

	fovmemaddress = iw5spmodule + 0x185757C;

	while (WriteProcessMemory(hProc, (LPVOID)fovmemaddress, &fov, sizeof(float), NULL)) Sleep(100);
}

void fov::Changer::setfov_mp(const HANDLE hProc) const
{
	if (!hProc) return;

	DWORD fovmemaddress;
	DWORD iw5mpmodule;

	iw5mpmodule = processhook::GetModuleBaseAddress(hProc, L"iw5mp.exe");

	if (!iw5mpmodule) return;

	fovmemaddress = iw5mpmodule + 0x55E8EC4;

	while (WriteProcessMemory(hProc, (LPVOID)fovmemaddress, &fov, sizeof(float), NULL)) Sleep(100);
}

fov::SettingsManager::SettingsManager(Changer * const pchanger)
{
}

void fov::SettingsManager::safeDefaultFov(float newfov)
{
	TCHAR szPath[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath))) {

		wcscat_s(szPath, L"\\mw3fovchanger\\config.cfg");
		HANDLE hFile = CreateFile(szPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		std::stringstream ss;
		ss << newfov;

		std::string s = ss.str();

		WriteFile(hFile, s.c_str(), s.length(), NULL, NULL);

		CloseHandle(hFile);
	}
}
