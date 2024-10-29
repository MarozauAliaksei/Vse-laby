#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>
#include <algorithm>

using namespace std;

struct NameOfFile
{
	string date, name;
	NameOfFile(){}
	NameOfFile(string s)
	{
		regex pattern(R"(([A-Za-z]+)_(\d{2})(\d{2})(\d{4})\..+\b)");
		smatch file_match;
		if (regex_search(s, file_match, pattern))
		{
			name = file_match[1];
			date = file_match[4];
			date += file_match[3];
			date += file_match[2];
		}
		else
		{
			name = "0";
		}
	}
	string GetDate()
	{
		return date.substr(6, 2) + date.substr(4, 2) + date.substr(0, 4);
	}
	//NameOfFile(const NameOfFile& other) : name(other.name), date(other.date){}
	/*NameOfFile& operator= (const NameOfFile& other)
	{
		name = other.name;
		date = other.date;
		return *this;
	}*/
};

int CountDifferentPref(const vector <NameOfFile>& v)
{
	map <string, string> mp;
	for (auto i : v)
	{
		mp[i.name] = i.date;
	}
	return mp.size();
}

bool comp(const NameOfFile& a, const NameOfFile& b)
{
	if (a.name == b.name)
	{
		return a.date > b.date;
	}
	return a.name > b.name;
}

vector<NameOfFile> FindMaxDateForPref(vector <NameOfFile> v)
{
	vector<NameOfFile> res;
	sort(v.begin(), v.end(), comp);
	res.push_back(v[0]);
	for (auto i : v)
	{
		if (i.name != res[res.size() - 1].name)
		{
			res.push_back(i);
		}
		else
		{
			res[res.size() - 1].date = max(res[res.size() - 1].date, i.date);
		}
	}
	return res;
}

int main()
{
	//cout << R"(\n)" << "\n"; //литерал
	//regex pattern(R"(([A-Za-z]+)_(\d{8})\.(.+)\b)");
	int n;
	cin >> n;
	vector <NameOfFile> v;
	cin.get();
	for (int i = 0; i < n; i++)
	{
		string s;
		getline(cin, s);
		NameOfFile nf(s);
		if (nf.name != "0")
		{
			v.push_back(nf);
		}
		/*if (regex_search(s, file_match, pattern))
		{
			cout << '\n';
			for (auto i : file_match)
			{
				cout << i << '\n';
			}
		}
		else
		{
			cout << "No match\n";
		}*/
	}
	cout << CountDifferentPref(v) << '\n';
	v = FindMaxDateForPref(v);
	for (auto i : v)
	{
		cout << i.name << ": " << i.GetDate() << '\n';
	}
	return 0;
}
