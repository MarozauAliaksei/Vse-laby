// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

int main()
{
    bool b1, b2;
    int i, result;
    cin >> i;


    result = !(i < -5 || i >= 6) ?
        (i % 2 > 0 ? i * i : i) :
        (i >= 9 || i < -8 ? i * i * i : i * -1);
    cout << result;
}
