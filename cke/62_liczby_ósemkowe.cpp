#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

constexpr size_t ARRAY_SIZE = 1000;

string ToString(int value, int base) {
    string result;

    while(value != 0) {
        result += "0123456789"[value % base];
        value /= base;
    }

    reverse(result.begin(), result.end());
    return result;
}

struct Data {
public:
    explicit Data(int base)
        : base(base)
        , numbers() { }

    Data(const Data&) = delete;

    decltype(auto) MinMax() const {
        return minmax_element(numbers.begin(), numbers.end());
    }

    pair<int, size_t> FindLongestSequence() const {
        int firstElementOfLongest = 0;
        size_t lengthOfLongest = 0;

        int firstElement = 0;
        size_t length = 1;
        int previous = numeric_limits<int>::max();

        for(int number : numbers) {
            if(number < previous) {
                if(length > lengthOfLongest) {
                    lengthOfLongest = length;
                    firstElementOfLongest = firstElement;
                }

                length = 0;
                firstElement = number;
            }

            ++length;
            previous = number;
        }

        return make_pair(firstElementOfLongest, lengthOfLongest);
    }

    template<typename Comp>
    size_t CountCorrectComparasions(const Data& other, Comp comp) const {
        size_t counter = 0;

        for(size_t it = 0; it < ARRAY_SIZE; ++it) {
            if(comp(numbers[it], other.numbers[it])) {
                ++counter;
            }
        }

        return counter;
    }

    size_t Count6(int baseOfNumber) const {
        size_t counter = 0;

        for(int number : numbers) {
            const string str = ToString(number, baseOfNumber);
            counter += count(str.begin(), str.end(), '6');
        }

        return counter;
    }

private:
    int base;
    array<int, ARRAY_SIZE> numbers;

public:
    friend istream& operator>>(istream& stream, Data& data) {
        size_t it = 0;
        for(string temp; stream >> temp;) {
            data.numbers[it] = stoi(temp, nullptr, data.base);
            ++it;
        }

        return stream;
    }
};

class Program {
public:
    Program()
        : data8(8)
        , data10(10) {
        ios_base::sync_with_stdio(false);

        ifstream("liczby1.txt") >> data8;
        ifstream("liczby2.txt") >> data10;
    }

    void Run() {
        Task1();
        Task2();
        Task3();
        Task4();
    }

private:
    void Task1() {
        auto [minIt, maxIt] = data8.MinMax();
        cout << "1)\n";
        cout << "min = " << ToString(*minIt, 8) << '\n';
        cout << "max = " << ToString(*maxIt, 8) << '\n';
        cout << '\n';
    }

    void Task2() {
        auto [firstElement, size] = data10.FindLongestSequence();
        cout << "2)\n";
        cout << "pierwszy element: " << firstElement << '\n';
        cout << "dlugosc: " << size << '\n';
        cout << '\n';
    }

    void Task3() {
        cout << "3)\n";
        cout << "taka sama wartosc: " << data8.CountCorrectComparasions(data10, equal_to<>{}) << '\n';
        cout << "liczby1 > liczby2: " << data8.CountCorrectComparasions(data10, greater<>{}) << '\n';
        cout << '\n';
    }

    void Task4() {
        cout << "4)\n";
        cout << "w zapisie 10: " << data10.Count6(10) << '\n';
        cout << "w zapisie 8: " << data10.Count6(8) << '\n';
        cout << '\n';
    }

    Data data8;
    Data data10;
};

int main() {
    Program program;
    program.Run();
}