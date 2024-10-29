#include <iostream>
#include<map>
#include <string>
#include<set>
#include<string>
#include <cmath>
using namespace std;
int Max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}
int main()
{
	int n;
	cin >> n;
	for (; n != 0; n--) {
		map<int, int> student_time;
		int timer = 1;
		int number_of_students;
		cin >> number_of_students;
		for (int i = 0; i < number_of_students; i++) {
			int	waiting_time, arrive_time;
			cin >> arrive_time >> waiting_time;
			if (arrive_time > timer) {
				timer = arrive_time;
			}
			if (timer <= waiting_time) {
				student_time[i] = timer;
				++timer;
			}
			else {
				student_time[i] = 0;
			}
		}
		for (auto iter : student_time ) {
			cout << iter.second << ' ';
		}
		cout << endl;
	}
}