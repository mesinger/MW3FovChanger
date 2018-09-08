#pragma once

#include <Windows.h>

namespace processhook {

	/*Get PID by passed process window name*/
	UINT GetProcessId(const char* wndname);

	/*Get a module base address by passed modulename, and handle to process*/
	DWORD GetModuleBaseAddress(const HANDLE& hProc, const wchar_t* modulename);
}