#pragma once

#include <Windows.h>

class FovChanger
{
public:
	FovChanger();
	~FovChanger();

	/*fov changing functions for singleplayer, this method blocks execution*/
	void ChangeFOV_SP(const HANDLE hProc, float fov);
	/*fov changing functions for multiplayer, this method blocks execution*/
	void ChangeFOV_MP(const HANDLE hProc, float fov);
};

