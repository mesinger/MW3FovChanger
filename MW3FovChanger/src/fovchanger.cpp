#include "FovChanger.h"
#include "processhook.h"
#include <iostream>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <string>

fov::Changer::Changer(float fov)
	:fov(fov)
{
	CHAR szPath[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, szPath))) {

		strcat_s(szPath, "\\mw3fovchanger\\config.cfg");

		OFSTRUCT reopenbuff;
		HFILE hfile = OpenFile(szPath, &reopenbuff, OF_READ);

		if (hfile != HFILE_ERROR) {

			char buf[64];
			DWORD bytesread;
			if (ReadFile((HANDLE)hfile, buf, 64, &bytesread, NULL)) {

				buf[bytesread] = '\0';
				float configFov = std::strtof(buf, nullptr);

				this->fov = configFov;
			}

			CloseHandle((HANDLE)hfile);
		}
	}
}

fov::Changer::~Changer()
{
	fov::updateConfig(fov);
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

void fov::updateConfig(float fov)
{
	TCHAR szPath[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath))) {

		wcscat_s(szPath, L"\\mw3fovchanger");
		CreateDirectory(szPath, NULL);

		wcscat_s(szPath, L"\\config.cfg");
		HANDLE hFile = CreateFile(szPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE) return;

		std::string s = std::to_string(fov);

		WriteFile(hFile, s.c_str(), s.length(), NULL, NULL);

		CloseHandle(hFile);
	}
}
