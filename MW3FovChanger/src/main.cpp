#include <Windows.h>
#include <iostream>
#include "processhook.h"
#include "FovChanger.h"
#include <thread>

#define VK_KEY_1 0x31

/*this method blocks execution*/
void userInputForFovChanger(fov::Changer* const pchanger);

int main(int argc, char** argv) {

	fov::Changer fovchanger;

	std::thread uithread(userInputForFovChanger, &fovchanger);

	/*Connect to process*/
	DWORD pid = 0;
	HANDLE hProc = NULL;

	/*Connect to either, MP or SP*/
	while (!pid) {

		//Singleplayer
		pid = processhook::GetProcessId("Call of Duty®: Modern Warfare® 3");
		if (pid) {

			hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

			if (hProc) {

				std::cout << "Attached to MW3" << std::endl;

				MessageBeep(MB_OKCANCEL);
				fovchanger.setfov_sp(hProc);
			}

			break;
		}

		//Multiplayer
		pid = processhook::GetProcessId("Call of Duty®: Modern Warfare® 3 Multiplayer");
		if (pid) {

			hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

			if (hProc) {

				std::cout << "Attached to MW3" << std::endl;

				MessageBeep(MB_OKCANCEL);
				fovchanger.setfov_mp(hProc);
			}

			break;
		}

		Sleep(100);
	}

	CloseHandle(hProc);
	uithread.join();

	MessageBeep(MB_OKCANCEL);

	return EXIT_SUCCESS;
}

void userInputForFovChanger(fov::Changer* const pchanger)
{
	std::cout << "MW3 Fov Changer (Developed with love by Mesinger)" << std::endl;
	std::cout << "[1] Set default FOV" << std::endl;
	std::cout << "[+] Increase FOV by 5" << std::endl;
	std::cout << "[-] Decrease FOV by 5" << std::endl << std::endl;

	std::cout << "Please start MW3..." << std::endl;

	fov::SettingsManager fovmgr(pchanger);

	while (true) {

		if (GetAsyncKeyState(VK_KEY_1)) {

			std::cout << "Enter new fov[0 - 180]: ";

			float fov;
			std::cin >> fov;

			if (!std::cin.fail()) {
				std::cout << std::endl << "Invalid input" << std::endl;
				continue;
			}
			
			if (pchanger->changeFov(fov)) {
				fovmgr.safeDefaultFov(fov);
			}
		}
		else if (GetAsyncKeyState(VK_ADD)) {

			float oldfov = pchanger->getFov();
			pchanger->changeFov(oldfov + 5.f);
		}
		else if (GetAsyncKeyState(VK_SUBTRACT)) {

			float oldfov = pchanger->getFov();
			pchanger->changeFov(oldfov - 5.f);
		}

		Sleep(100);
	}
}
