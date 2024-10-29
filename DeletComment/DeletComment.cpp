#include <iostream>
#include <regex>
#include<fstream>

using namespace std;
int main()
{
	regex pattern1(R"(//.*)");
	regex pattern2(R"(/\*.*?\*/)");
	regex pattern3(R"(nEwLinE)");
	ifstream fin("Input.cpp");
	ofstream fout("Output.cpp");
	while (!fin.eof()) {
		string s;
		getline(fin, s);
		s = regex_replace(s, pattern1, "");
		fout << s << "nEwLinE";
	}
	fin.close();
	fout.close();
	ifstream fin1("Output.cpp");
	ofstream fout1("Output2.cpp");
	string s;
	getline(fin1, s);
	s = regex_replace(s, pattern2, "");
	s = regex_replace(s, pattern3, "\n");
	fout1 << s;
	fin1.close();
	fout1.close();
}