#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <utility>
#include <vector>

using namespace std;

bool IsCubeOfNaturalNumber(int value) {
    const double root = cbrt(value);
    return root == trunc(root);
}

int MostCommonElement(const vector<int>& data) {
    map<int, size_t> counter;
    for(int datum : data) {
        ++counter[datum];
    }

    return max_element(counter.begin(), counter.end(),
                       [](const auto& left, const auto& right) {
                           return left.second < right.second;
                       })
        ->first;
}

class Sequence {
public:
    int GetDifference() const {
        return terms[1] - terms[0];
    }

    bool IsArithmetic() const {
        const int difference = GetDifference();

        for(auto it = terms.begin() + 2; it != terms.end(); ++it) {
            if(*it - *(it - 1) != difference) {
                return false;
            }
        }

        return true;
    }

    optional<int> GetCubeOfNaturalNumber() const {
        int cube = 0;

        for(int term : terms) {
            if(IsCubeOfNaturalNumber(term)) {
                cube = max(term, cube);
            }
        }

        if(cube == 0) {
            return nullopt;
        } else {
            return cube;
        }
    }

    int FindMistake() const {
        vector<int> differences(terms.size() - 1);

        for(size_t index = 0; index < differences.size(); ++index) {
            differences[index] = terms[index + 1] - terms[index];
        }

        const int difference = MostCommonElement(differences);

        for(size_t index = 0; index < differences.size() - 1; ++index) {
            if(differences[index] != difference) {
                if(differences[index + 1] != difference) {
                    return terms[index + 1];
                }

                return terms[index];
            }
        }

        return terms.back();
    }

private:
    friend istream& operator>>(istream& stream, Sequence& sequence) {
        if(size_t length; stream >> length) {
            sequence.terms.resize(length);
            for(int& term : sequence.terms) {
                stream >> term;
            }
        }

        return stream;
    }

    vector<int> terms;
};

class Program {
public:
    Program() {
        ifstream file("ciagi.txt");

        for(Sequence temp; file >> temp;) {
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
        size_t arithmeticSequenceCounter = 0;
        int maxDifference = 0;

        for(auto&& sequence : sequences) {
            if(sequence.IsArithmetic()) {
                ++arithmeticSequenceCounter;
                maxDifference = max(sequence.GetDifference(), maxDifference);
            }
        }

        cout << "1)\n";
        cout << "arithmetic sequences: " << arithmeticSequenceCounter << '\n';
        cout << "max difference: " << maxDifference << '\n';
    }

    void Task2() {
        cout << "2)\n";

        for(auto&& sequence : sequences) {
            if(optional<int> result = sequence.GetCubeOfNaturalNumber(); result.has_value()) {
                cout << *result << '\n';
            }
        }
    }

    void Task3() {
        ifstream file("bledne.txt");

        cout << "3)\n";
        for(Sequence sequence; file >> sequence;) {
            cout << sequence.FindMistake() << '\n';
        }
    }

    vector<Sequence> sequences;
};

int main() {
    Program program;
    program.Run();
}