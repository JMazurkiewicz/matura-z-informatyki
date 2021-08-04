#include <algorithm>
#include <bitset>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class BinaryInt {
public:
    bool IsEven() const {
        return value.back() == '0';
    }

    unsigned long GetValue() const {
        return stoul(value, nullptr, 2);
    }

    bool operator<(const BinaryInt& other) const {
        return GetValue() < other.GetValue();
    }

    size_t DigitCount() const {
        return value.size();
    }

private:
    string value;

    friend istream& operator>>(istream& stream, BinaryInt& binInt) {
        return stream >> binInt.value;
    }

    friend ostream& operator<<(ostream& stream, const BinaryInt& binInt) {
        return stream << binInt.value;
    }
};

class Program {
public:
    Program() {
        ifstream file("liczby.txt");
        copy(istream_iterator<BinaryInt>{file}, istream_iterator<BinaryInt>{}, back_inserter(binaryIntegers));
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        cout << "1) ";
        cout << count_if(binaryIntegers.begin(), binaryIntegers.end(), mem_fn(&BinaryInt::IsEven));
        cout << '\n';
    }

    void Task2() {
        const auto maxIter = max_element(binaryIntegers.begin(), binaryIntegers.end());

        cout << "2)\n";
        cout << *maxIter << '\n';
        cout << maxIter->GetValue() << '\n';
    }

    void Task3() {
        const size_t count = count_if(binaryIntegers.begin(), binaryIntegers.end(),
                                      [](const BinaryInt& binInt) { return binInt.DigitCount() == 9; });

        const unsigned long sum =
            accumulate(binaryIntegers.begin(), binaryIntegers.end(), 0UL, [](unsigned long sum, const BinaryInt& term) {
                return sum + (term.DigitCount() == 9 ? term.GetValue() : 0UL);
            });

        cout << "3)\n";
        cout << "ile: " << count << '\n';
        cout << "suma: " << bitset<32>{sum} << '\n';
    }

    vector<BinaryInt> binaryIntegers;
};

int main() {
    Program program;
    program.Run();
}