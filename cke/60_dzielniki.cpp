#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

class Program {
public:
    Program() {
        ios_base::sync_with_stdio(false);
        LoadFromFile();
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void LoadFromFile() {
        ifstream file("liczby.txt");

        for(int& number : numbers) {
            file >> number;
        }
    }

    void Task1() {
        int counter = 0;
        int last1 = 0, last2 = 0;

        for(auto it = numbers.rbegin(); it != numbers.rend(); ++it) {
            if(*it < 1000) {
                ++counter;

                if(last1 == 0) {
                    last1 = *it;
                } else if(last2 == 0) {
                    last2 = *it;
                }
            }
        }

        cout << "1)\n";
        cout << "ilosc: " << counter << '\n';
        cout << "dwie ostatnie: " << last1 << ' ' << last2 << "\n\n";
    }

    void Task2() {
        cout << "2)\n";

        for(int number : numbers) {
            vector<int> divisors = {1};

            for(int d = 2; d <= number / 2; ++d) {
                if(number % d == 0) {
                    divisors.push_back(d);
                }

                if(divisors.size() > 18) {
                    break;
                }
            }

            if(divisors.size() == 17) {
                cout << number << ": ";
                for(int divisor : divisors) {
                    cout << divisor << ", ";
                }
                cout << number << '\n';
            }
        }

        cout << '\n';
    }

    void Task3() {
        int maxCoprime = numeric_limits<int>::min();
        bool isCoprime;

        for(size_t p = 0; p < numbers.size(); ++p) {
            isCoprime = true;

            for(size_t q = 0; q < numbers.size(); ++q) {
                if(p != q && gcd(numbers[p], numbers[q]) != 1) {
                    isCoprime = false;
                    break;
                }
            }

            if(isCoprime) {
                maxCoprime = max(maxCoprime, numbers[p]);
            }
        }

        cout << "3) " << maxCoprime << '\n';
    }

    array<int, 200> numbers;
};

int main() {
    Program program;
    program.Run();
}