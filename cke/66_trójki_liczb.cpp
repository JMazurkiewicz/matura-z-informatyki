#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

using Int = uintmax_t;

struct Triplet {
    Int a;
    Int b;
    Int c;
};

ostream& operator<<(ostream& stream, const Triplet& triplet) {
    return stream << triplet.a << ' ' << triplet.b << ' ' << triplet.c;
}

constexpr Int SumOfDigits(Int value) {
    Int sum = 0;

    while(value != 0) {
        sum += value % 10;
        value /= 10;
    }

    return sum;
}

constexpr bool IsPrime(Int value) {
    for(Int d = 2; d * d <= value; ++d) {
        if(value % d == 0) {
            return false;
        }
    }

    return true;
}

constexpr Int Pow2(Int value) {
    return value * value;
}

bool IsRightTriangleCreatableWith(const Triplet& triplet) {
    array<Int, 3> array{triplet.a, triplet.b, triplet.c};
    sort(array.begin(), array.end());

    return Pow2(array[0]) + Pow2(array[1]) == Pow2(array[2]);
}

constexpr bool IsTriangleCreatableWith(const Triplet& triplet) {
    return triplet.a + triplet.b > triplet.c && triplet.c + triplet.a > triplet.b && triplet.b + triplet.c > triplet.a;
}

class Program {
public:
    Program() {
        ifstream file("trojki.txt");

        for(Int a, b, c; file >> a >> b >> c;) {
            triplets.push_back(Triplet{a, b, c});
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
        cout << "1)\n";
        for(auto [a, b, c] : triplets) {
            if(SumOfDigits(a) + SumOfDigits(b) == c) {
                cout << Triplet{a, b, c} << '\n';
            }
        }
    }

    void Task2() {
        cout << "2)\n";
        for(auto [a, b, c] : triplets) {
            if(IsPrime(a) && IsPrime(b) && a * b == c) {
                cout << Triplet{a, b, c} << '\n';
            }
        }
    }

    void Task3() {
        cout << "3)\n";
        for(auto it = triplets.begin() + 1; it != triplets.end(); ++it) {
            if(IsRightTriangleCreatableWith(*it) && IsRightTriangleCreatableWith(*(it - 1))) {
                cout << *(it - 1) << '\n';
                cout << *it << '\n';
            }
        }
    }

    void Task4() {
        size_t longestSequenceLength = 0;
        size_t currentSequenceLength = 0;

        for(auto&& triplet : triplets) {
            if(IsTriangleCreatableWith(triplet)) {
                ++currentSequenceLength;

            } else {
                longestSequenceLength = max(currentSequenceLength, longestSequenceLength);
                currentSequenceLength = 0;
            }
        }

        cout << "4) " << max(currentSequenceLength, longestSequenceLength) << '\n';
    }

    vector<Triplet> triplets;
};

int main() {
    Program program;
    program.Run();
}