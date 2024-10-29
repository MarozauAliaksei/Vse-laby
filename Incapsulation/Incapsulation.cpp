#include <iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
class Figure{
    public:
        Figure() : figure_name_("default"){}
        virtual double Area() const = 0;
        virtual double Perimetr() const = 0;
        virtual void Print() {
        cout << "This is Figure " << figure_name_ << "!" << endl;
        }
        virtual string GetName() {
            return figure_name_;
        }
protected:
        string figure_name_;
private:
    string secret_variable_;

};

class Square : public Figure {
public:
    Square(int side, string name) : side_(side) {
        figure_name_ = name;
    }
    double Area() const {
        return side_ * side_;
    }
    double Perimetr() const {
        return 4 * side_;
    }
    void Print() {
        cout << "This is a Square " << figure_name_ << "!" << endl;
    }
private:
    double side_;
};

class Circle : public Figure {
public:
    double Area() const {
        return 3.14 * radius_ * radius_;
    }
    double Perimetr() const {
        return 3.14 * 2 * radius_;
    }
    Circle(double radius, string figure_name) : radius_(radius) {
        figure_name_ = figure_name;
    }
    double GetRadius() {
        return radius_;
    }
    void Print() {
        cout << "This is a Circle " << figure_name_ << "!" << endl;
    }

private:
    double radius_;
};
int main()
{
    Circle circle(3, "ABC");
    cout << circle.GetRadius() << " " << circle.Area() << " " << circle.Perimetr() << endl;
    circle.Print();
    Figure* fig = new Circle(3, "fig");
    fig->Print();
    static_cast<Circle*>(fig)->GetRadius();
    vector<Figure*> figures{
    new Circle(3,"CIrcl"),
    new Square(3, "sqr")
    };
    Square square(4, "ABCD");
    square.Print();
    for (int i = 0; i < figures.size(); i++) {
        cout << "Figure N " << i + 1 << endl;
        cout << "Figure Name: " << figures[i]->GetName() << endl;
        cout << "Figure Area: " << figures[i]->Area() << endl;
    }
    return 0;
}
