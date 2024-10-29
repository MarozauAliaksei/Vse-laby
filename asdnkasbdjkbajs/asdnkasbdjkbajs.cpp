#pragma warning(disable:4996) 
#include <iostream> 
#include <fstream> 
#include <algorithm> 
#include <cstring> 
using namespace std;

struct Item {
    char Name[35];
    char myDate[8];
    char Section[10];
    int Count;
    Item() {
        strcpy(Name, "____");
        strcpy(myDate, "____");
        strcpy(Section, "____");
        Count = 0;
    }
    friend istream& operator>>(istream& in, Item& a) {
        in >> a.Name >> a.myDate >> a.Section >> a.Count;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Item& a) {
        out << a.Name << "\t" << a.myDate << "\t" << a.Section << "\t" << a.Count;
        return out;
    }
    friend bool operator==(const Item& f, const Item& s) {
        return strcmp(f.Name, s.Name) == 0;
    }
};

struct Price {
    char Name[30];
    char myDate[8];
    double pr;
    Price() {
        strcpy(Name, "____");
        strcpy(myDate, "____");
        pr = 0;
    }
    friend istream& operator>>(istream& in, Price& a) {
        in >> a.Name >> a.myDate >> a.pr;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Price& a) {
        out << a.Name << "\t" << a.myDate << "\t" << a.pr;
        return out;
    }
    friend bool operator==(const Price& f, const Price& s) {
        return strcmp(f.Name, s.Name) == 0;
    }
};

struct Med {
    char Name[35];
    char myDate[8];
    char Section[10];
    double pr;
    int count;
    Med() {
        strcpy(Name, "____");
        strcpy(Section, "____");
        strcpy(myDate, "____");
        count = 0;
        pr = 0.0;
    }
    Med& operator=(const Item& a) {
        strcpy(Name, a.Name);
        strcpy(myDate, a.myDate);
        strcpy(Section, a.Section);
        pr = 0;
        count = a.Count;
        return *this;
    }
    Med& operator=(const Price& a) {
        strcpy(Name, a.Name);
        strcpy(myDate, a.myDate);
        strcpy(Section, "unknown");
        pr = a.pr;
        count = 0;
        return *this;
    }
    friend istream& operator>>(istream& in, Med& a) {
        in >> a.Name >> a.Section >> a.pr >> a.count;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Med& a) {
        out << a.Name << "\t" << a.myDate << "\t" << a.Section << "\t" << a.pr << "\t" << a.count;
        return out;
    }
    friend bool operator==(const Med& f, const Med& s) {
        return strcmp(f.Name, s.Name) == 0;
    }
};


template <class T>
class MED {
private:
    int count;
    T* M;
public:
    MED() {
        count = 1;
        M = new T[1];
    }
    MED(int n_count) {
        count = n_count;
        M = new T[count];
    }
    ~MED() {
        delete[] M;
    }
    T& operator[](int ind) {
        return M[ind];
    }
    MED& operator=(MED& a) {
        delete[] M;
        count = a.count;
        M = new T[count];
        for (int i = 0; i < count; i++) {
            M[i] = a.M[i];
        }
        return *this;
    }
    int GetCount() {
        return count;
    }
    void Push(T& value) {
        T* MM = new T[count + 1];
        for (size_t i = 0; i < count; i++) {
            MM[i] = M[i];
        }
        delete[] M;
        MM[count] = value;
        M = MM;
        count++;
    }
    void ReadData(string fileName_binary) {
        T temp;
        fstream f1(fileName_binary, fstream::in | fstream::out | ios::binary);
        while (!f1.eof()) {
            f1.read((char*)&temp, sizeof(temp));
            if (f1.good()) {
                Push(temp);
            }
        }
    }
    void WriteData(char* fileName_binary) {
        ofstream f(fileName_binary, ios::out | ios::binary);
        for (int i = 0; i < count; i++) {
            f.write((char*)&M[i], sizeof(M[i]));
        }
    }
    ostream& PutData(ostream& out) {
        setlocale(LC_ALL, "RUS");
        for (int i = 1; i < count; i++) {
            if (strcmp(M[i].Name, "____") == 0) {
                break;
            }
            out << M[i] << endl;
        }
        return out;
    }
    void transform_to_binary(string filename, string filename_binary) {
        ifstream in(filename);
        ofstream out(filename_binary, ios::binary);
        T temp;
        while (in) {
            in >> temp;
            if (in.eof()) {
                break;
            }
            out.write((char*)&temp, sizeof(temp));
        }
    }
    void Sort() {
        sort(M + 1, M + count, [](const T& i, const T& j) {
            return strcmp(i.Name, j.Name) < 0;
            }
        );
    }
    T* Find(string name) {
        for (int i = 0; i < count; i++) {
            if (M[i].Name == name) {
                return &M[i];
            }
        }
        return nullptr;
    }

};



int main() {
    MED <Item> M1;
    MED <Price> K1;
    string filename = "Текст.txt";
    char filename1[50] = "Текст1.txt";
    string filename_b = "F1.bin";
    char filename_b1[50] = "F2.bin";
    M1.transform_to_binary(filename, filename_b);
    M1.ReadData(filename_b);
    M1.PutData(cout);
    cout << endl;
    if (M1.Find("Dox") != nullptr) {
        cout << *(M1.Find("Dox"));
    }
    else {
        cout << "Товар не найден";
    }
    cout << endl;
    cout << endl;
    M1.Sort();
    M1.PutData(cout);
    cout << endl;
    K1.transform_to_binary(filename1, filename_b1);
    K1.ReadData(filename_b1);
    K1.PutData(cout);
    cout << endl;
    if (K1.Find("Alph") != nullptr) {
        cout << *(K1.Find("Alph"));
    }
    else {
        cout << "Товар не найден";
    }
    cout << endl;
    cout << endl;
    K1.Sort();
    K1.PutData(cout);
    cout << endl;
    MED <Med> R(M1.GetCount() + K1.GetCount());
    int ind = 0;
    for (int i = 0; i < M1.GetCount(); i++) {
        R[i] = M1[i];
        ind = i;
    }
    for (int i = 0; i < K1.GetCount(); i++) {
        if (R.Find(K1[i].Name) == nullptr) {
            R[ind + 1] = K1[i];
            ind++;
        }
    }
    R.PutData(cout);
}