#include <windows.h>
#include <iostream>
using namespace std;
// функция для вывода сообщения об ошибке на консоль на русском языке
void CoutErrorMessage()
{
	char prefix[] = "Ошибка Win32 API: ";
	LPVOID lpMsgBuf;
// перекодируем заголовок
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // язык по умолчанию
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	// перекодируем русские буквы

	// выводим сообщение об ошибке на консоль
	cout << prefix << (char*)lpMsgBuf << endl;
	// освобождаем буфер
	LocalFree(lpMsgBuf);
}
int main()
{
	setlocale(LC_ALL, "rus");
	HANDLE hHandle = NULL;
	// неправильный вызов функции закрытия дескриптора
	if (!CloseHandle(hHandle))
		CoutErrorMessage();
	return 0;
}