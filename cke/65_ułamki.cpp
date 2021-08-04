#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

using Int = std::uintmax_t;

constexpr Int B = 2 * 2 * 3 * 3 * 5 * 5 * 7 * 7 * 13;

struct Fraction {
    Int num, denom;

    constexpr Fraction Short() const {
        const Int gcd = std::gcd(num, denom);
        return {num / gcd, denom / gcd};
    }

    constexpr bool IsNotShortable() const {
        return std::gcd(num, denom) == 1;
    }

    friend istream& operator>>(istream& stream, Fraction& fraction) {
        return stream >> fraction.num >> fraction.denom;
    }

    friend ostream& operator<<(ostream& stream, const Fraction& fraction) {
        return stream << fraction.num << ' ' << fraction.denom;
    }
};

constexpr bool operator==(const Fraction& left, const Fraction& right) {
    const Fraction leftShort = left.Short();
    const Fraction rightShort = right.Short();

    return leftShort.num == rightShort.num && leftShort.denom == rightShort.denom;
}

constexpr bool operator<(const Fraction& left, const Fraction& right) {
    if(left == right) {
        return left.denom < right.denom;
    }

    return left.num * right.denom < left.denom * right.num;
}

constexpr Fraction operator+(const Fraction& left, const Fraction& right) {
    const Int num = left.num * right.denom + left.denom * right.num;
    const Int denom = left.denom * right.denom;

    return Fraction{num, denom}.Short();
}

class Program {
public:
    Program() {
        ifstream file("dane_ulamki.txt");

        for(Fraction temp; file >> temp;) {
            fractions.push_back(temp);
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
        cout << "1) " << *min_element(fractions.begin(), fractions.end()) << '\n';
    }

    void Task2() {
        cout << "2) " << count_if(fractions.begin(), fractions.end(), mem_fn(&Fraction::IsNotShortable)) << '\n';
    }

    void Task3() {
        Int result = 0;

        for(auto&& fraction : fractions) {
            result += fraction.Short().num;
        }

        cout << "3) " << result << '\n';
    }

    void Task4() {
        const Fraction sum = accumulate(fractions.begin(), fractions.end(), Fraction{0, 1});
        const Int result = (B / sum.denom) * sum.num;

        cout << "4) " << result << '\n';
    }

    vector<Fraction> fractions;
};

int main() {
    Program program;
    program.Run();
}