#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool IsDuocyclic(const string& sequence) {
    if(sequence.size() % 2 != 0) {
        return false;
    }

    const auto middle = sequence.begin() + (sequence.size() / 2);

    return equal(sequence.begin(), middle, middle, sequence.end());
}

bool HasNoConnectingOnes(const string& sequence) {
    return sequence.find("11") == std::string::npos;
}

constexpr bool IsSemiprime(int value) {
    size_t divisorCounter = 0;

    int temp = value;

    for(int d = 2; d <= value / 2; ++d) {
        while(temp % d == 0) {
            ++divisorCounter;

            if(divisorCounter > 2) {
                return false;
            }

            temp /= d;
        }
    }

    return divisorCounter == 2;
}

class Program {
public:
    Program() {
        ifstream file("ciagi.txt");

        for(string temp; file >> temp;) {
            sequences.push_back(move(temp));
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

        for(auto&& sequence : sequences) {
            if(IsDuocyclic(sequence)) {
                cout << sequence << '\n';
            }
        }
    }

    void Task2() {
        cout << "2) ";
        cout << count_if(sequences.begin(), sequences.end(), HasNoConnectingOnes) << '\n';
    }

    void Task3() {
        size_t counter = 0;

        int minValue = numeric_limits<int>::max();
        int maxValue = numeric_limits<int>::min();

        for(auto&& sequence : sequences) {
            const int value = stoi(sequence, nullptr, 2);

            if(IsSemiprime(value)) {
                ++counter;

                minValue = min(value, minValue);
                maxValue = max(value, maxValue);
            }
        }

        cout << "3)\n";
        cout << "semiprime count: " << counter << '\n';
        cout << "min semiprime: " << minValue << '\n';
        cout << "max semiprime: " << maxValue << '\n';
    }

    vector<string> sequences;
};

int main() {
    Program program;
    program.Run();
}