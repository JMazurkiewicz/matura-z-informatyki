#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

enum class Quarter { I = 1, II = 2, III = 3, IV = 4, UNSPECIFIED = -1 };

ostream& operator<<(ostream& stream, Quarter quarter) {
    switch(quarter) {
    case Quarter::I:
        return stream << "I";

    case Quarter::II:
        return stream << "II";

    case Quarter::III:
        return stream << "III";

    case Quarter::IV:
        return stream << "IV";

    case Quarter::UNSPECIFIED:
        return stream << "quarter not specified";
    }

    stream.setstate(ios_base::failbit);
    return stream;
}

struct Circle {
    double x;
    double y;
    double r;

    Quarter GetQuarter() const {
        if(abs(x) < r || abs(y) < r) {
            return Quarter::UNSPECIFIED;
        }

        if(x > 0 && y > 0) {
            return Quarter::I;
        }

        if(x < 0 && y > 0) {
            return Quarter::II;
        }

        if(x < 0 && y < 0) {
            return Quarter::III;
        }

        return Quarter::IV;
    }

    constexpr bool IsMirrorOf(const Circle& other) const {
        if(r != other.r) {
            return false;
        }

        return (-x == other.x && y == other.y) || (-y == other.y && x == other.x);
    }

    constexpr bool IsPerpendicularWith(const Circle& other) const {
        if(r != other.r) {
            return false;
        }

        return (-other.x == y && other.y == x) || (-x == other.y && y == other.x);
    }

    bool IsNeighbourOf(const Circle& other) const {
        const double distance = hypot(x - other.x, y - other.y);

        return (distance <= r + other.r) && (distance >= abs(r - other.r));
    }

    friend istream& operator>>(istream& stream, Circle& circle) {
        return stream >> circle.x >> circle.y >> circle.r;
    }
};

class Program {
public:
    Program() {
        ifstream file("okregi.txt");

        for(Circle temp; file >> temp;) {
            circles.push_back(temp);
        }
    }

    void Run() {
        Task1();
        Task2();
        Task3();
        Task4();
    }

private:
    void Task1() {
        map<Quarter, size_t> counter;

        for(auto&& circle : circles) {
            ++counter[circle.GetQuarter()];
        }

        cout << "1)\n";
        for(auto [quarter, count] : counter) {
            cout << quarter << ": " << count << '\n';
        }
    }

    void Task2() {
        size_t counter = 0;

        for(auto p = circles.begin(); p != circles.end(); ++p) {
            for(auto q = p + 1; q != circles.end(); ++q) {
                if(p->IsMirrorOf(*q)) {
                    ++counter;
                }
            }
        }

        cout << "2) " << counter << '\n';
    }

    void Task3() {
        size_t counter = 0;

        for(auto p = circles.begin(); p != circles.end(); ++p) {
            for(auto q = p + 1; q != circles.end(); ++q) {
                if(p->IsPerpendicularWith(*q)) {
                    ++counter;
                }
            }
        }

        cout << "3) " << counter << '\n';
    }

    void Task4() {
        cout << "4)\n";

        size_t maxLength = 0;
        size_t currentLength = 1;

        for(auto it = circles.begin() + 1; it != circles.begin() + 1000; ++it) {
            if(it->IsNeighbourOf(*(it - 1))) {
                ++currentLength;

            } else {
                cout << currentLength << ' ';

                maxLength = max(currentLength, maxLength);
                currentLength = 1;
            }
        }

        cout << currentLength << '\n';
        maxLength = max(currentLength, maxLength);

        cout << "longest sequence: " << maxLength << '\n';
    }

    vector<Circle> circles;
};

int main() {
    Program program;
    program.Run();
}