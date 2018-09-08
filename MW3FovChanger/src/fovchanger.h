#pragma once

#include <Windows.h>

namespace fovchanger {

	/*fov changing functions for singleplayer, this method blocks execution*/
	void ChangeFOV_SP(const HANDLE hProc, float fov);
	/*fov changing functions for multiplayer, this method blocks execution*/
	void ChangeFOV_MP(const HANDLE hProc, float fov);
}

