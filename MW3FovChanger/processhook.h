#pragma once

#include <Windows.h>

namespace processhook {

	/*Get PID by passed process window name*/
	UINT GetProcessId(const char* wndname);
	
	/*Open connection to process by passed pid, returns HANDLE to process*/
	HANDLE ConnectToProcess(DWORD pid);

	/*Get a module base address by passed modulename, and handle to process*/
	DWORD GetModuleBaseAddress(const HANDLE& hProc, const char* modulename);
}