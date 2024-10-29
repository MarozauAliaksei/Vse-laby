#include <iostream>
#include<algorithm>
#include <vector>
#include<string>
#include <fstream>
#include <cmath>
#include<iomanip>
using namespace std;

struct S1 {
    string Name;
    int Price;
    bool RedPrice;

    S1() {
        Name = "noname";
        Price = 0;
        RedPrice = false;
    }

    friend ostream& operator<<(ostream& out, S1& prod1);
    friend istream& operator>>(istream& in, S1& prod1);
    friend bool operator==(S1& prod1, S1& prod2);
    friend bool operator<(const S1& prod1, const S1& prod2);

};
ostream& operator<<(ostream& out, S1& prod1)
{
    out << prod1.Name << ' ' << prod1.Price << prod1.RedPrice;
    return out;
}
istream& operator>>(istream& in, S1& prod1)
{
    in >> prod1.RedPrice >> prod1.Price;
    getline(in, prod1.Name);
    return in;
}
bool operator==(S1& prod1, S1& prod2)
{
    return (prod1.Name == prod2.Name);
}
bool operator<(const S1& prod1, const S1& prod2)
{
    return prod1 < prod2;
}


struct S2 {
    string Name;
    int Ammount;
    bool RedPrice;

    S2() {
        Name = "noname";
        Ammount = 0;
        RedPrice = false;
    }

    friend ostream& operator<<(ostream& out, S2& bag1);
    friend istream& operator>>(istream& in, S2& bag1);
    friend bool operator==(S2& ba1, S2& bag2);
    friend bool operator<(const S2& bag1, const S2& bag2);
};
ostream& operator<<(ostream& out, S2& bag1)
{
    out << bag1.Name << ' ' << bag1.Ammount << bag1.RedPrice;
    return out;
}
istream& operator>>(istream& in, S2& bag1)
{
    in >> bag1.Ammount >> bag1.RedPrice;
    getline(in, bag1.Name);
    return in;
}
bool operator==(S2& bag1, S2& bag2)
{
    return bag1.Name == bag2.Name;
}
bool operator<(const S2& bag1, const S2& bag2)
{
    return bag1.Name < bag2.Name;
}

struct S3 {
    string Name;
    int Price;
    bool Ammount;

    S3() {
        Name = "noname";
        Ammount = 0;
        Price = 0;
    }

    friend ostream& operator<<(ostream& out, S3& nrp1);
    friend istream& operator>>(istream& in, S3& nrp1);
    friend bool operator==(S3& nrp1, S3& nrp2);
    friend bool operator<(const S3& nrp1, const S3& nrp2);
};
ostream& operator<<(ostream& out, S3& nrp1)
{
    out << nrp1.Name << ' ' << nrp1.Ammount << nrp1.Price;
    return out;
}
istream& operator>>(istream& in, S3& nrp1)
{
    in >> nrp1.Ammount >> nrp1.Price;
    getline(in, nrp1.Name);
    return in;
}
bool operator==(S3& nrp1, S3& nrp2)
{
    return nrp1.Name == nrp2.Name;
}
bool operator<(const S3& nrp1, const S3& nrp2)
{
    return nrp1.Name < nrp1.Name;
}

class ABS_LIB {
public:
    virtual void ReadData(string filename) = 0;
    virtual void PutData(ostream& out) const = 0;
    virtual void Intersect(ABS_LIB* first, ABS_LIB* second) = 0;
    virtual void Sort() = 0;
    virtual void Cout() = 0;

};
class Prod : public ABS_LIB {
private:
    int count;
    S1* arr;
public:
    Prod() {
        count = 0;
        arr = nullptr;
    }
    ~Prod() {
        delete[] arr;
    }
    void ReadData(string file_name) {
        ifstream fin(file_name);
        vector<S1> tmpbg;
        for (int i = 0; fin.peek() != EOF; i++) {
            S1 tmp;
            fin >> tmp;
            tmpbg.push_back(tmp);
            count++;
        }
        arr = new S1[count];
        for (int i = 0; i < tmpbg.size(); i++) {
            arr[i] = tmpbg[i];
        }
        fin.close();
    }
    virtual void PutData(ostream& out) const override {
        for (int i = 0; i < count; i++) {
            out << arr[i] << endl;
        }
    }
    void Intersect(ABS_LIB* first, ABS_LIB* second)  {
        if (arr != nullptr) delete[] arr;
        arr = new S1[((Prod*)first)->count + ((Prod*)second)->count];
        first->Sort();
        second->Sort();
        int i = 0, j = 0, s = 0;
        for (; i < ((Prod*)first)->count && j < ((Prod*)second)->count;) {
            if ((*(Prod*)first).arr[i] == (*(Prod*)second).arr[j]) {
                arr[s] = (*(Prod*)first).arr[i];
                ++s; ++i; ++j;
            }
            else if ((*(Prod*)first).arr[i] < (*(Prod*)second).arr[j]) ++i;
            else ++j;
        }
        count = s;
    }

    void Sort() override {
        sort(arr, arr + count, [](S1 A, S1 B) {return A.Name < B.Name; });
    }
    void Cout() override {
        for (int i = 0; i < count; i++) {
            cout << arr[i] << endl;
        }
    }
};

class Bag : public ABS_LIB {
private:
    int count;
    S2* arr;
public:
    Bag() {
        count = 0;
        arr = nullptr;
    }
    ~Bag() {
        delete[] arr;
    }
    void ReadData(string file_name) {
        ifstream fin(file_name + ".txt");
        vector<S2> tmpbg;
        for (int i = 0; fin.peek() != EOF; i++) {
            S2 tmp;
            fin >> tmp;
            tmpbg.push_back(tmp);
            count++;
        }
        arr = new S2[count];
        for (int i = 0; i < tmpbg.size(); i++) {
            arr[i] = tmpbg[i];
        }
        fin.close();
    }

    virtual void PutData(ostream& out) const override {
        for (int i = 0; i < count; i++) {
            out << arr[i] << endl;
        }
    }
    void Intersect(ABS_LIB* first, ABS_LIB* second) override {

    }
    Bag Intersect(Bag other) {
        Bag tmp;
        int i, j;
        vector<S2> result;
        for (i = 0, j = 0; i < count && j < other.count;) {
            if (arr[i].Name == other.arr[j].Name) {
                result.push_back(arr[i]);
                i++;
                j++;
                continue;
            }
            if (arr[i].Name < other.arr[j].Name) {
                result.push_back(arr[i]);
                i++;
                continue;
            }
            if (arr[i].Name > other.arr[j].Name) {
                result.push_back(other.arr[j]);
                j++;
            }
        }
        for (; i < count; i++) {
            result.push_back(arr[i]);
        }
        for (; j < other.count; j++) {
            result.push_back(other.arr[j]);
        }
        tmp.arr = new S2[result.size()];
        tmp.count = result.size();
        for (int i = 0; i < result.size(); i++) {
            tmp.arr[i] = result[i];
        }
        return tmp;
    }
    void Sort() override {
        sort(arr, arr + count, [](S2 A, S2 B) {return A.Name < B.Name; });
    }
    void Cout() override {
        for (int i = 0; i < count; i++) {
            cout << arr[i] << endl;
        }
    }
}; class NotRedPrice : public ABS_LIB {
private:
    int count;
    S3* arr;
public:
    NotRedPrice() {
        count = 0;
        arr = nullptr;
    }
    ~NotRedPrice() {
        delete[] arr;
    }
    void ReadData(string file_name) override {
        ifstream fin(file_name + ".txt");
        vector<S3> tmpbg;
        for (int i = 0; fin.peek() != EOF; i++) {
            S3 tmp;
            fin >> tmp;
            tmpbg.push_back(tmp);
            count++;
        }
        arr = new S3[count];
        for (int i = 0; i < tmpbg.size(); i++) {
            arr[i] = tmpbg[i];
        }
        fin.close();
    }
    virtual void PutData(ostream& out) const override {
        for (int i = 0; i < count; i++) {
            out << arr[i] << endl;
        }
    }
    void Intersect(ABS_LIB* first, ABS_LIB* second) override {

    }
    void Sort() override {
        sort(arr, arr + count, [](S3 A, S3 B) {return A.Name < B.Name; });
    }
    void Cout() override {
        for (int i = 0; i < count; i++) {
            cout << arr[i] << endl;
        }
    }
};


int main()
{
    Prod M1;
    Bag K1;
    NotRedPrice R;
    ABS_LIB* A1, * A2, * A3, * A4;

    M1.ReadData("Prod1.txt");
    M1.Cout();  
    return 1;
}