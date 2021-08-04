#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template<typename Type>
constexpr Type Pow2(Type value) {
    return value * value;
}

struct Point {
    int x;
    int y;

    constexpr bool IsInFirstQuarter() const {
        return x > 0 && y > 0;
    }

    friend istream& operator>>(istream& stream, Point& point) {
        return stream >> point.x >> point.y;
    }

    friend ostream& operator<<(ostream& stream, const Point& point) {
        return stream << '(' << point.x << ", " << point.y << ')';
    }
};

double Distance(const Point& one, const Point& two) {
    return hypot(one.x - two.x, one.y - two.y);
}

struct Triplet {
    Point a;
    Point b;
    Point c;

    constexpr bool AreInFirstQuarter() const {
        return a.IsInFirstQuarter() && b.IsInFirstQuarter() && c.IsInFirstQuarter();
    }

    constexpr bool AreOnOneLine() const {
        return (b.y - a.y) * (c.x - a.x) == (c.y - a.y) * (b.x - a.x);
    }

    double GetTriangleCircumference() const {
        return Distance(a, b) + Distance(b, c) + Distance(c, a);
    }

    bool IsRightTriangleCreatebleWith() const {
        array<int, 3> sidesSquared = {Pow2(a.x - b.x) + Pow2(a.y - b.y), Pow2(b.x - c.x) + Pow2(b.y - c.y),
                                      Pow2(c.x - a.x) + Pow2(c.y - a.y)};

        sort(sidesSquared.begin(), sidesSquared.end());
        return sidesSquared[0] + sidesSquared[1] == sidesSquared[2];
    }

    constexpr Point CalculatePointD() const {
        return Point{c.x + a.x - b.x, c.y + a.y - b.y};
    }

    friend istream& operator>>(istream& stream, Triplet& triplet) {
        return stream >> triplet.a >> triplet.b >> triplet.c;
    }
};

class Program {
public:
    Program() {
        ifstream file1("wspolrzedne.txt");
        copy(istream_iterator<Triplet>{file1}, istream_iterator<Triplet>{}, back_inserter(points));

        ifstream file2("wspolrzedneTR.txt");
        copy(istream_iterator<Triplet>{file2}, istream_iterator<Triplet>{}, back_inserter(trianglePoints));
    }

    void Run() {
        Task1();
        Task2();
        Task3();
        Task4();
        Task5();
    }

private:
    void Task1() {
        cout << "1) " << count_if(points.begin(), points.end(), mem_fn(&Triplet::AreInFirstQuarter)) << '\n';
    }

    void Task2() {
        cout << "2) " << count_if(points.begin(), points.end(), mem_fn(&Triplet::AreOnOneLine)) << '\n';
    }

    void Task3() {
        const auto largestTriangle =
            max_element(trianglePoints.begin(), trianglePoints.end(), [](const Triplet& left, const Triplet& right) {
                return left.GetTriangleCircumference() < right.GetTriangleCircumference();
            });

        cout << "3)\n";
        cout << 'A' << largestTriangle->a << '\n';
        cout << 'B' << largestTriangle->b << '\n';
        cout << 'C' << largestTriangle->c << '\n';

        cout << fixed << setprecision(2);
        cout << "L = " << largestTriangle->GetTriangleCircumference() << '\n';
    }

    void Task4() {
        cout << "4) "
             << count_if(trianglePoints.begin(), trianglePoints.end(), mem_fn(&Triplet::IsRightTriangleCreatebleWith))
             << '\n';
    }

    void Task5() {
        cout << "5)\n";

        for(auto&& triplet : trianglePoints) {
            if(const Point d = triplet.CalculatePointD(); d.x == d.y) {
                cout << 'A' << triplet.a << ", B" << triplet.b << ", C" << triplet.c << ", D" << d << '\n';
            }
        }
    }

    vector<Triplet> points;
    vector<Triplet> trianglePoints;
};

int main() {
    Program program;
    program.Run();
}