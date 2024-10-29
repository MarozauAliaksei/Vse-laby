#include <iostream>
using namespace std;
int Positive(int a) {
	__asm {
		mov eax , a
		cmp eax, 0
		jg positive
		neg eax
		jmp end_
		positive :

		end_ :

	}
}
int Max(int* a, int n) {
	n--;
	__asm {
		mov esi, a
		mov ecx, n
		mov edx, 0
		mov edi, 0
		mov eax, [esi]
		check:
		mov ebx, [esi + 4]
		cmp ebx, eax
		jg bolshe
		add edx, 1
		jmp enda
		bolshe:
		add edx, 1
		mov edi, edx
		mov eax, ebx
		enda:
		add esi, 4
		loop check
		mov eax, edi
	}
}
int main()

{
	setlocale(LC_ALL, "Russian");
	int* a;
	int n = 0;
	cout << "Введите размер массива: ";
	cin >> n;
	a = new int[n];
	cout << endl << "Введите элементы массива: ";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n;i++) {
		cout << a[i];
		if (Positive(a[i])) {
			cout << Positive(a[i]) << endl;
		}
		else {
			cout << " Not Positive" << endl;
		}
	}
	cout << "Максимальный элемент массива: " << Max(a,n) << endl;
}
