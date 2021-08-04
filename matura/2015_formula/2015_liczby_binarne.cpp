#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using namespace std;

constexpr bool IsDivisibleBy2(string_view number) {
    return number.back() == '0';
}

constexpr bool IsDivisibleBy8(string_view number) {
    if(number.size() <= 3) {
        return false;
    }

    number.remove_prefix(number.size() - 3);
    return number == "000"sv;
}

constexpr bool CompareNumbers(string_view left, string_view right) {
    left.remove_prefix(left.find('1'));
    right.remove_prefix(right.find('1'));

    if(left.size() != right.size()) {
        return left.size() < right.size();
    }

    return left < right;
}

class Program {
public:
    Program() {
        ifstream file("liczby.txt");
        for(string temp; file >> temp;) {
            numbers.push_back(move(temp));
        }
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        cout << "1) ";
        cout << count_if(numbers.begin(), numbers.end(), [](const string& number) {
            return count(number.begin(), number.end(), '0') > static_cast<ptrdiff_t>(number.size() / 2);
        });
        cout << '\n';
    }

    void Task2() {
        cout << "2)\n";
        cout << "n%2 == 0: " << count_if(numbers.begin(), numbers.end(), IsDivisibleBy2) << '\n';
        cout << "n%8 == 0: " << count_if(numbers.begin(), numbers.end(), IsDivisibleBy8) << '\n';
    }

    void Task3() {
        cout << "3)\n";

        const auto [minIt, maxIt] = minmax_element(numbers.begin(), numbers.end(), CompareNumbers);

        const size_t minPosition = (minIt - numbers.begin()) + 1;
        const size_t maxPosition = (maxIt - numbers.begin()) + 1;

        cout << "min: " << minPosition << '\n';
        cout << "max: " << maxPosition << '\n';
    }

    vector<string> numbers;
};

int main() {
    Program program;
    program.Run();
}