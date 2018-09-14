#include <Windows.h>
#include <iostream>
#include "processhook.h"
#include "FovChanger.h"
#include <future>
#include <memory>

#define VK_KEY_1 0x31

int main(int argc, char** argv) {

	std::cout << "MW3 Fov Changer (Developed with love by Mesinger)" << std::endl;
	std::cout << "[+[NUMPAD]] Increase FOV by 5" << std::endl;
	std::cout << "[-[NUMPAD]] Decrease FOV by 5" << std::endl << std::endl;

	std::cout << "Please start MW3..." << std::endl;

	while (true) {

		fov::Changer fovchanger;

		/*Connect to process*/
		DWORD pid = 0;
		HANDLE hProc = NULL;

		std::unique_ptr<std::future<void>> worker;

		/*Connect to either, MP or SP*/
		while (!pid) {

			//Singleplayer
			pid = processhook::GetProcessId("Call of Duty®: Modern Warfare® 3");
			if (pid) {

				hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

				if (hProc) {

					std::cout << "Attached to MW3" << std::endl;

					MessageBeep(MB_OKCANCEL);
					worker = std::make_unique<std::future<void>>(std::async(&fov::Changer::setfov_sp, &fovchanger, hProc));
					break;
				}
			}

			//Multiplayer
			pid = processhook::GetProcessId("Call of Duty®: Modern Warfare® 3 Multiplayer");
			if (pid) {

				hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

				if (hProc) {

					std::cout << "Attached to MW3" << std::endl;

					MessageBeep(MB_OKCANCEL);
					worker = std::make_unique<std::future<void>>(std::async(&fov::Changer::setfov_mp, &fovchanger, hProc));
					break;
				}
			}

			Sleep(100);
		}

		while (worker->wait_for(std::chrono::milliseconds(25)) != std::future_status::ready) {

			if (GetAsyncKeyState(VK_ADD)) {

				float oldfov = fovchanger.getFov();
				fovchanger.changeFov(oldfov + 5.f);
				Sleep(125);
			}
			else if (GetAsyncKeyState(VK_SUBTRACT)) {

				float oldfov = fovchanger.getFov();
				fovchanger.changeFov(oldfov - 5.f);
				Sleep(125);
			}
		}

		CloseHandle(hProc);

		std::cout << "Detached from MW3" << std::endl;
	}

	return EXIT_SUCCESS;
}
