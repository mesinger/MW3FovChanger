#pragma once

#include <Windows.h>

namespace memext {

	/*Write access*/
	template<typename T>
	BOOL write(HANDLE hProc, LPVOID dest, T src, size_t size) {
		return WriteProcessMemory(hProc, dest, src, size, nullptr);
	}
}