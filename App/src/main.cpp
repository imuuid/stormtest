#include "main.h"
#include <Windows.h>
#include <cstdio>
#include <thread>

DWORD WINAPI MainThread(HMODULE hModule) {
	if (!checkstart()) {
		std::thread server(startServer);
		std::thread drive(driver);
		server.join();
		return 0;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

  
