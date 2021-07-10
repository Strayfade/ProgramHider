#include <iostream>
#include <Windows.h>
#include <shellapi.h>

#define WM_MYMESSAGE (WM_USER + 1)

bool isWindowHidden = false;

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = GetConsoleWindow();
	nid.uID = 100;
	nid.uVersion = NOTIFYICON_VERSION;
	nid.uCallbackMessage = WM_MYMESSAGE;
	nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	if (!Shell_NotifyIconA(NIM_ADD, &nid))
	{
		MessageBox(0, "Failed to mount to System Tray.", "Strayfade ProgramHider", MB_OK);
	}
	HWND hiddenWindow = NULL;
	while (!GetAsyncKeyState(VK_INSERT))
	{
		if (GetAsyncKeyState(0xDC) & 1)
		{
			if (!isWindowHidden)
			{
				hiddenWindow = GetForegroundWindow();
				ShowWindow(hiddenWindow, SW_HIDE);
				isWindowHidden = !isWindowHidden;
			}
			else if (isWindowHidden)
			{
				ShowWindow(hiddenWindow, SW_SHOW);
				isWindowHidden = !isWindowHidden;
			}
			Sleep(500);
		}
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			if (isWindowHidden)
			{
				ShowWindow(GetConsoleWindow(), SW_SHOW);
				system("cls");
				std::cout << " <> Input X: \n";
				int x;
				int y;
				std::cin >> x;
				system("cls");
				std::cout << " <> Input Y: \n";
				std::cin >> y;
				ShowWindow(GetConsoleWindow(), SW_HIDE);
				SetWindowPos(hiddenWindow, NULL, 1, 1, x, y, SWP_ASYNCWINDOWPOS);
				ShowWindow(hiddenWindow, SW_SHOW);
			}
			else if (!isWindowHidden)
			{
				MessageBox(0, "Hey You! Yeah, you need to hide a window before its size can be changed. To choose a window, select it and press Backslash. Then, press DELETE to set a window Size!", "Strayfade ProgramHider", MB_OK);
			}
		}
	}
}