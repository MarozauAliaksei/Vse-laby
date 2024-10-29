#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	int* arr;
	int n;
	cout << "Enter size of array and it elements:\n";
	cin >> n;
	arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	char* a = new char[8];
	int radix = 10;
	/*string temp = "";
	for (int i = 0; i < n; i++) {
		temp += _itoa(arr[i], a, radix);
		temp += ' ';
	}*/

	char args[1000];
	strcpy_s(args,_itoa(n, a, radix));
	for (int i = 0; i < n; i++) {
		strcat_s(args, " ");
		strcat_s(args, _itoa(arr[i], a , radix));
	}

	int color;
	cout << "Enter color of console, enter 1 for Red, 2 for Green, 3 for Blue:\n";
	cin >> color;
	char lpszAppName[] = "C:\\Users\\user\\source\\repos\\Laba2\\x64\\Debug\\Project3.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USEFILLATTRIBUTE;
	switch (color) {
	case 1:
		si.dwFillAttribute = BACKGROUND_RED;
		break;
	case 2:
		si.dwFillAttribute = BACKGROUND_GREEN;
		break;
	case 3:
		si.dwFillAttribute = BACKGROUND_BLUE;
		break;
	default:
		cout << "Wrong input. Background color set default";
		break;
	}

	cout << args;
	// создаем новый консольный процесс
	if (!CreateProcessA((LPCSTR)lpszAppName, args, nullptr, nullptr, FALSE,
		CREATE_NEW_CONSOLE, nullptr, nullptr, (LPSTARTUPINFOA)&si, &piApp))
	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	_cputs("The new process is created.\n");
	// ждем завершения созданного прцесса
	WaitForSingleObject(piApp.hProcess, INFINITE);
	// закрываем дескрипторы этого процесса в текущем процессе
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	return 0;
}