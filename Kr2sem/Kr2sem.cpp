#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
struct Campus {
    string name;
    int id;
    Campus() : id(0), name("Empty") {}
    friend istream& operator>>(istream& in, Campus& camp) {
        in >> camp.id;
        getline(in, camp.name);
        return in;
    }
    friend ostream& operator<<(ostream& out, Campus& cam) {
        out << cam.ToString();
        return out;
    }
    virtual string ToString() const {
        return to_string(id) + name;
    }
    virtual void BinaryRead(istream& in)
    {
        in.seekg(0, in.ios::end);
        int pos = in.tellg();
        in.seekg(in.ios::beg);
        char* str = new char[pos];
        in.read(str, pos);
        string s(str);
        id = stoi(s.substr(0, s.find_first_of(' ')));
        name = s.substr(s.find_first_of(' ') + 1, s.find_last_of(' ') - s.find_first_of(' ') - 1);
    }

};

struct Library {
    int id;
    string name;
    int debt;
    Library() : id(0),name("Empty"),debt(0) {}
    friend istream& operator>>(istream& in, Library& lib) {
        in >> lib.id >> lib.debt;
        getline(in, lib.name);
        return in;
    }
    friend ostream& operator<<(ostream& out, Library& lib) {
        out << lib.ToString();
        return out;
    }
    string ToString() const{
        string tmp = to_string(id) + ' ' + to_string(debt) + name;
        return tmp;
    }
    virtual void BinaryRead(istream& in) 
    {
        in.seekg(0, in.ios::end);
        int pos = in.tellg();
        in.seekg(in.ios::beg);
        char* str = new char[pos + 1];
        in.read(str, pos);
        str[pos] = 0;
        string s(str);
        id = stoi(s.substr(0, s.find_first_of(' ')));
        name = s.substr(s.find_first_of(' ') + 1, s.find_last_of(' ') - s.find_first_of(' ') - 1);
        debt = stod(s.substr((s.find_last_of(' ') + 1, s.size() - s.find_last_of(' ') - 1)));
    }
    virtual void BinaryWrite(ostream& out) const 
    {
        out.write(ToString().c_str(), sizeof(char) * ToString().size());
    }
};
template<class T>
class Stud {
public:
    int Size(){
        return size_;
    }

    void FromText(string file_name) {
        ifstream fin(file_name + ".txt");
        for (int i = 0; fin.peek() != EOF;i++) {
            T tmp;
            fin >> tmp;
            arr_.push_back(tmp);
            size_++;
        }
        fin.close();
    }
    void ToText(string file_name) {
        ofstream fout(file_name + ".txt");
        for (int i = 0; i < size_; i++) {
            fout << arr_[i] << '\n';
        }
        fout.close();
    }
    void SortStud() {
        sort(arr_.begin(), arr_.end(), [](T A, T B) {return A.id < B.id; });
    }
    string findStud(int n) {
        string result;
        bool flag = 0;
        for (int i = 0; i < size_; i++) {
            if (arr_[i].id == n) {
                result = arr_[i].name;
                flag = 1;
            }
        }
        if (!flag) {
            result = "No such Person";
        }
        return result;
    }
    T& operator[](int value) {
        return arr_[value];
    }
private:
    vector<T> arr_;
    int size_;
};
int main()
{
    Stud<Library> stud_library;
    stud_library.FromText("Test2");
    stud_library.ToText("ResultLibNoSort"); //В файле не отсортированная структура
    stud_library.SortStud(); 
    cout << stud_library.findStud(123213) << ' ' << stud_library.findStud(12312123123121) << endl; // ищем студентов 
    stud_library.ToText("ResultLib"); // Тут отсортИрованная структура
    Stud<Campus> stud_campus;
    stud_campus.FromText("Test");
    stud_campus.ToText("ResultCamNoSort");
    stud_campus.SortStud();
    cout << stud_campus.findStud(945687) << ' ' << stud_campus.findStud(123123545345) << endl;
    stud_campus.ToText("ResultCam");
    ofstream fout1("Binoutput.txt", ios::binary | ios::out);
    ofstream binaryFile("Result.bin", ios::binary);
    if (binaryFile.is_open()) {
        for (int i = 0; i < stud_library.Size();i++) {
            binaryFile.write(reinterpret_cast<const char*>(&stud_library[i]), sizeof(Stud<Library>));
        }
        binaryFile.close();
        cout << "Results written to binary file: Result.bin" << endl;
    }
    fout1.close();
}
