#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int main()
{
    ifstream in("input.txt");
    string str;
    int sum = 0;
    set<int> st;
    while (getline(in, str)) {
        int a = stol(str);
        bool flag = st.count(a);
        if (!flag) {
            sum += a;
            st.insert(a);
        }
    }
    ofstream out("output.txt");
    out << sum;
    return 0;
}