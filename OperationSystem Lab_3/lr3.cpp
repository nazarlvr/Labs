#include <bits/stdc++.h>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#include "psapi.h"

using namespace std;

HHOOK hHook{ NULL };

string getKey(DWORD wVirtKey)
{
    string s;

    switch(wVirtKey)
    {
    case VK_DELETE:
        s = "[DELETE]";
        break;
    case VK_BACK:
        s = "[BACK]";
        break;
    case VK_RSHIFT:
        s = "[RIGHT SHIFT]";
        break;
    case VK_LSHIFT:
        s = "[LEFT SHIFT]";
        break;
    case VK_RCONTROL:
        s = "[RIGHT CONTROL]";
        break;
    case VK_LCONTROL:
        s = "[LEFT CONTROL]";
        break;
    case VK_TAB:
        s = "[TAB]";
        break;
    default:
        s.push_back(wVirtKey);
    }

    return s;
}

LRESULT CALLBACK keyboard_hook(const int code, const WPARAM wParam, const LPARAM lParam) {
	if (wParam == WM_KEYDOWN)
    {
		KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;

		cout << getKey(wVirtKey);
	}

	return CallNextHookEx(hHook, code, wParam, lParam);
}

int main(int argc, char* argv[])
{
    string windowname = "D:\\os\\lr3process.exe";
    DWORD pid, cbNeeded;
    HMODULE hMods[1024];
	HWND hwnd = FindWindow(NULL, windowname.c_str());
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

	EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded);

	for (int i = 0; i < cbNeeded; ++i)
	{
	    MODULEINFO mi;
	    DWORD nSize = 1024, *lpBuffer = (DWORD*) malloc(sizeof(DWORD) * nSize);
	    SIZE_T lpNumberOfBytesRead;

	    GetModuleInformation(hProcess, hMods[i], &mi, sizeof(mi));
	    ReadProcessMemory(hProcess, mi.EntryPoint, lpBuffer, nSize, &lpNumberOfBytesRead);
	    cout << "Module " << i << endl;

	    for (int j = 0; j < lpNumberOfBytesRead; ++j)
            cout << lpBuffer[j] << ' ';

        cout << endl;
	}

	///

	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, NULL, 0);

	if (hHook == NULL) {
		cout << "Keyboard hook failed!" << endl;
	}

	while (GetMessage(NULL, NULL, 0, 0));
    return 0;
}
