#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream in("report.in");
	int n;
	in >> n;
	vector<int> days;
	for (int i = 0; i < n; i++) {
		int tmp;
		in >> tmp;
		days.push_back(tmp);
	}
	
	int k = 0;
	for (int i = 1, j = 1; i < n / 2 + 1;) {
    	if (days[i] > days[i - 1] && days[n - 1 - j] > days[n - j]) {
			if (i != n - 1 - j) {
				k++;
			}
			i++;
			j++;
			continue;
		}
		if ((days[i] < days[i - 1])) {
			i++;
			continue;
		}
		j++;

	}


	cout << k << endl;
	int i = 0;
	vector<int> temp(2 * k + 1);
	for (; i < k; i++) {
		temp[i] = days[i];
		temp[2 * k - i] = days[n - i];
	}
	if (k == 0) {
		temp[0] = days[0];
	}
	else {
		if (days[i + 1] > days[n - i - 1]) {
			temp[k + 1] = days[i + 1];
		}
		else
		{
			temp[k + 1] = days[n - i - 1];
		}
	}
	
	for (int i = 0; i < temp.size(); i++) {
		cout << temp[i] << ' ';
	}
	cout << endl;
	return 0;
}
