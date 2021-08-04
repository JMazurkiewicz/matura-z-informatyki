#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct PairOfWords : public pair<string, string> {
    bool DoSatisfyTask1() const {
        const auto minmax = std::minmax(first.size(), second.size());
        return (minmax.second / minmax.first) >= 3;
    }

    bool DoSatisfyTask2() const {
        return second.size() >= first.size() && second.compare(0, first.size(), first) == 0;
    }

    string GetSuffixOfSecond() const {
        return second.substr(first.size());
    }

    size_t GetCommonEndingLength() const {
        const auto mismatchResult = std::mismatch(first.rbegin(), first.rend(), second.rbegin(), second.rend());

        return mismatchResult.first - first.rbegin();
    }

    friend istream& operator>>(istream& stream, PairOfWords& pairs) {
        return stream >> pairs.first >> pairs.second;
    }

    friend ostream& operator<<(ostream& stream, PairOfWords& pairs) {
        return stream << pairs.first << ' ' << pairs.second;
    }
};

class Program {
public:
    Program() {
        ifstream file("napisy.txt");

        for(PairOfWords temp; file >> temp;) {
            pairs.push_back(move(temp));
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

        bool isFirst = true;
        size_t counter = 0;

        for(auto&& pairOfWords : pairs) {
            if(pairOfWords.DoSatisfyTask1()) {
                if(isFirst) {
                    cout << pairOfWords << '\n';
                    isFirst = false;
                }

                ++counter;
            }
        }

        cout << counter << '\n';
    }

    void Task2() {
        cout << "2)\n";

        for(auto&& pairOfWords : pairs) {
            if(pairOfWords.DoSatisfyTask2()) {
                cout << pairOfWords << ' ' << pairOfWords.GetSuffixOfSecond() << '\n';
            }
        }
    }

    void Task3() {
        sort(pairs.begin(), pairs.end(), [](const PairOfWords& left, const PairOfWords& right) {
            return left.GetCommonEndingLength() > right.GetCommonEndingLength();
        });

        const size_t longesEnding = pairs.front().GetCommonEndingLength();

        cout << "3)\n" << longesEnding << '\n';

        for(auto it = pairs.begin(); it != pairs.end(); ++it) {
            if(it->GetCommonEndingLength() == longesEnding) {
                cout << *it << '\n';
            } else {
                break;
            }
        }
    }

    vector<PairOfWords> pairs;
};

int main() {
    Program program;
    program.Run();
}