#pragma once
#include <windows.h>
#include <string>
#include "main.h"
#include <tlhelp32.h>
using namespace std;


//Magic function
bool click = false;
void driver(){
    HWND hwnd = FindWindow("LWJGL", nullptr);
    while (true) {
        int newDelay = (90 / fDelay) * 10;
        if (GetAsyncKeyState(keyB)) {
            click = !click;
            Sleep(150);
        }

        if (GetKeyState(VK_LBUTTON) & 0x8000 && click)
        {
            PostMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
            PostMessage(hwnd, WM_LBUTTONUP, 0, 0);
            Sleep(newDelay);
        }
    }
}

//Processes
BOOL IsProcessRunning(DWORD pid)
{
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD ret = WaitForSingleObject(process, 0);
    CloseHandle(process);
    return ret == WAIT_TIMEOUT;
}

DWORD getPID(LPCTSTR ProcessName)
{
    PROCESSENTRY32 pt;
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pt.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hsnap, &pt)) {
        do {
            if (!lstrcmpi(pt.szExeFile, ProcessName)) {
                CloseHandle(hsnap);
                return pt.th32ProcessID;
            }
        } while (Process32Next(hsnap, &pt));
    }
    CloseHandle(hsnap);
    return 0;
}

bool checkstart() 
{
    DWORD DriverPID = getPID(TEXT("AnyDesk.exe"));
    bool check = IsProcessRunning(DriverPID);
    return check;
}

