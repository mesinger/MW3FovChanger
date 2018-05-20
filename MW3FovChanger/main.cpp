#include <Windows.h>
#include <iostream>
#include "processhook.h"
#include "FovChanger.h"

int main(int argc, char** argv) {

	/*Connect to process*/
	DWORD pid = 0;
	HANDLE hProc = NULL;

	FovChanger fovchanger;

	/*Connect to either, MP or SP*/
	while (!pid) {

		//Singleplayer
		pid = processhook::GetProcessId("Call of Duty®: Modern Warfare® 3");
		if (pid) {

			hProc = processhook::ConnectToProcess(pid);

			if(hProc)
				fovchanger.ChangeFOV_SP(hProc, 90.f);

			break;
		}

		//Multiplayer
		pid = processhook::GetProcessId("Call of Duty®: Modern Warfare® 3 Multiplayer");
		if (pid) {

			hProc = processhook::ConnectToProcess(pid);

			if(hProc)
				fovchanger.ChangeFOV_MP(hProc, 90.f);

			break;
		}

		Sleep(100);
	}

	MessageBeep(MB_OKCANCEL);

	return EXIT_SUCCESS;
}