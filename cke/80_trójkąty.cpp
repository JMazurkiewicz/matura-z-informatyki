#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

constexpr int pow2(int value) {
    return value * value;
}

constexpr bool IsTriangleCreateableWith(int a, int b, int c) {
    return (a + b > c) && (b + c > a) && (c + a > b);
}

bool IsRightTriangleCreateableWith(int a, int b, int c) {
    if(!IsTriangleCreateableWith(a, b, c)) {
        return false;
    }

    array<int, 3> temp = {a, b, c};
    sort(temp.begin(), temp.end());

    return pow2(temp[0]) + pow2(temp[1]) == pow2(temp[2]);
}

class Program {
public:
    Program() {
        ifstream file("dane_trojkaty.txt");

        for(int temp; file >> temp;) {
            data.push_back(temp);
        }
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        cout << "1)\n";

        for(auto it = data.begin() + 2; it != data.end(); ++it) {
            if(IsRightTriangleCreateableWith(*it, *(it - 1), *(it - 2))) {
                cout << *it << ' ' << *(it - 1) << ' ' << *(it - 2) << '\n';
            }
        }
    }

    void Task2() {
        sort(data.begin(), data.end(), greater<int>{});

        auto it = data.begin() + 2;

        while(it != data.end()) {
            if(IsTriangleCreateableWith(*it, *(it - 1), *(it - 2))) {
                break;
            }

            ++it;
        }

        cout << "2) " << accumulate(it - 2, it + 1, 0) << '\n';
    }

    void Task3() {
        size_t counter = 0;

        for(auto p = data.begin(); p != data.end(); ++p) {
            for(auto q = p + 1; q != data.end(); ++q) {
                for(auto r = q + 1; r != data.end(); ++r) {
                    if(IsTriangleCreateableWith(*p, *q, *r)) {
                        ++counter;
                    }
                }
            }
        }

        cout << "3) " << counter << '\n';
    }

    vector<int> data;
};

int main() {
    Program program;
    program.Run();
}