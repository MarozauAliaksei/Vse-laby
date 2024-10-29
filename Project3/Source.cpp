#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

void shell_sort(int* array, int size) {
    for (int s = size / 2; s > 0; s /= 2) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
                int temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int size = atoi(argv[0]);
    int* arr = new int[size];
    for (int i = 1; i < size + 1; i++) {
        arr[i - 1] = atoi(argv[i]);
    }
    for (int i = 0; i < size; i++) {
        cout << arr[i] <<  ' ';
    }
    cout << endl;
    shell_sort(arr, size);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;

    cout << "Press any key to continue";
    _getch();
    return 0;
}