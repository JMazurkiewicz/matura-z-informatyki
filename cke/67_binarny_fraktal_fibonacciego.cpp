#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

using Int = std::intmax_t;

constexpr size_t FIB40_BIN_LENGTH = 27;

constexpr Int FibonacciNumber(size_t n) {
    if(n == 1 || n == 2) {
        return 1;
    }

    return FibonacciNumber(n - 1) + FibonacciNumber(n - 2);
}

constexpr bool IsPrime(Int value) {
    if(value == 1) {
        return false;
    }

    for(int div = 2; div * div <= value; ++div) {
        if(value % div == 0) {
            return false;
        }
    }

    return true;
}

string ToString(Int value, int base) {
    string result;

    while(value != 0) {
        result += "0123456789"[value % base];
        value /= base;
    }

    reverse(result.begin(), result.end());
    return result;
}

class Program {
public:
    void Run() {
        Task1();
        Task2();
        Task3();
        Task4();
    }

private:
    void Task1() {
        cout << "1)\n";
        cout << "F(10) = " << FibonacciNumber(10) << '\n';
        cout << "F(20) = " << FibonacciNumber(20) << '\n';
        cout << "F(30) = " << FibonacciNumber(30) << '\n';
        cout << "F(40) = " << FibonacciNumber(40) << '\n';
    }

    void Task2() {
        cout << "2)\n";

        for(size_t n = 1; n <= 40; ++n) {
            const Int fib = FibonacciNumber(n);

            if(IsPrime(fib)) {
                cout << "F(" << n << ") = " << fib << '\n';
            }
        }
    }

    void Task3() {
        cout << "3)\n" << right;

        for(Int n = 1; n <= 40; ++n) {
            cout << setw(FIB40_BIN_LENGTH) << setfill('0');
            cout << ToString(FibonacciNumber(n), 2) << '\n';
        }
    }

    void Task4() {
        cout << "4)\n";

        for(Int n = 1; n <= 40; ++n) {
            const string binary = ToString(FibonacciNumber(n), 2);

            if(count(binary.begin(), binary.end(), '1') == 6) {
                cout << binary << '\n';
            }
        }
    }
};

int main() {
    Program program;
    program.Run();
}