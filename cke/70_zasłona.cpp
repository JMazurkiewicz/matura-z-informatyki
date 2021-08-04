#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

using Real = double;

constexpr Real Pow(Real value, size_t exp) {
    return (exp == 0) ? (1) : (value * Pow(value, exp - 1));
}

constexpr Real Abs(Real value) {
    return (value < 0) ? (-value) : (value);
}

struct Point {
    Real x;
    Real y;
};

Real Distance(const Point& left, const Point& right) {
    return hypot(left.x - right.x, left.y - right.y);
}

struct Curtain {
private:
    static constexpr Real PRECISION = 0.001;
    static constexpr Real TRAPEZE_HEIGHT = PRECISION;
    static constexpr Real STRIP_WIDTH = 0.25;

    static constexpr Real Top() {
        return 19.0 + 61.0 / 125.0;
    }

    static constexpr Real Bottom() {
        return -(32.0 + 2.0 / 3.0);
    }

    static constexpr Real Left() {
        return 2.0;
    }

    static constexpr Real Right() {
        return 10.0;
    }

    static constexpr Real TopFunction(Real x) {
        return Pow(x, 4) / 500.0 - Pow(x, 2) / 200.0 - 3.0 / 250.0;
    }

    static constexpr Real BottomFunction(Real x) {
        return -Pow(x, 3) / 30.0 + x / 20.0 + 1.0 / 6.0;
    }

    static constexpr Real RectangleArea() {
        return Abs(Left() - Right()) * Abs(Bottom() - Top());
    }

    static constexpr Real TopArea() {
        Real area = 0.0;

        for(Real p = Left(); p < Right(); p += PRECISION) {
            const Real lowerBase = Abs(Top() - TopFunction(p));
            const Real upperBase = Abs(Top() - TopFunction(p + PRECISION));

            area += 0.5 * TRAPEZE_HEIGHT * (lowerBase + upperBase);
        }

        return area;
    }

    static constexpr Real BottomArea() {
        Real area = 0.0;

        for(Real p = Left(); p < Right(); p += PRECISION) {
            const Real lowerBase = Abs(Bottom() - BottomFunction(p));
            const Real upperBase = Abs(Bottom() - BottomFunction(p + PRECISION));

            area += 0.5 * TRAPEZE_HEIGHT * (lowerBase + upperBase);
        }

        return area;
    }

    static Real TopFunctionLength() {
        Real length = 0;

        for(Real p = Left(); p < Right(); p += PRECISION) {
            const Point a = {p, TopFunction(p)};
            const Point b = {p + PRECISION, TopFunction(p + PRECISION)};

            length += Distance(a, b);
        }

        return length;
    }

    static Real BottomFunctionLength() {
        Real length = 0;

        for(Real p = Left(); p < Right(); p += PRECISION) {
            const Point a = {p, BottomFunction(p)};
            const Point b = {p + PRECISION, BottomFunction(p + PRECISION)};

            length += Distance(a, b);
        }

        return length;
    }

    static constexpr Real LeftSideLength() {
        return Abs(Top() - Bottom());
    }

    static constexpr Real BaseLength() {
        return Abs(Left() - Right());
    }

public:
    static constexpr Real Task1() {
        return RectangleArea() - TopArea() - BottomArea();
    }

    static Real Task2() {
        return ceil(BottomFunctionLength() + TopFunctionLength() + 2 * BaseLength() + LeftSideLength());
    }

    static Real Task3() {
        Real sum = 0.0;

        for(Real p = Left(); p < Right(); p += STRIP_WIDTH) {
            sum += floor(Abs(TopFunction(p) - BottomFunction(p)));
        }

        return sum;
    }
};

int main() {
    cout << fixed << setprecision(3) << '\n';

    cout << "1) " << Curtain::Task1() << '\n';
    cout << "2) " << Curtain::Task2() << '\n';
    cout << "3) " << Curtain::Task3() << '\n';
}