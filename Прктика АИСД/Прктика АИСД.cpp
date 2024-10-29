#include <iostream>
#include <vector>;
using namespace std;

vector <unsigned long long> b;

//unsigned long long Fact(int x) {
//    if (x == 0) {
//        return 1;
//    }
//    return Fact(x - 1) * x;
//}
//unsigned long long Fibonachi(int x) {
//    if (x == 0) {
//        return 0;
//    }
//    if (x == 1) {
//        return 1;
//    }
//    return Fibonachi(x - 1) + Fibonachi(x - 2);
//}
//unsigned long long MFibonachi(int x) {
//    if (b[x] == -1) {
//        b[x] = MFibonachi(x - 1) + MFibonachi(x - 2);
//    }
//    return b[x];
//}
unsigned long long P(int x) {
    if (x == 1) {
        return 1;
    }
    return 2 * P(x - 1) + 1;
}

void H(int n, int a,int  b) {
    if (n == 0) {
        return;
    }
    H(n - 1, a, 6 - a - b);
    cout << a << "->" << b << endl;
    H(n - 1, 6 - a - b, b);
}

int main()
{
    int n;
    cin >> n;
    /*vector <unsigned long long> a(n + 1);
    a[0] = 1; a[1] = 1;
    for (int i = 2; i <= n; i++) {
        a[i] = a[i - 2] + a[i - 1];
    }
    b.resize(n + 1, -1);
    b[0] = 0; b[1] = 1;
    cout << a[n] << endl;
    cout << MFibonachi(n) << endl;*/
    H(n, 1, 3);
    cout << P(n);

}


