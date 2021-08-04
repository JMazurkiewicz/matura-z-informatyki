#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

constexpr char vowels[] = {'A', 'E', 'I', 'O', 'U', 'Y'};

constexpr bool IsConsonant(char letter) {
    for(char vowel : vowels) {
        if(letter == vowel) {
            return false;
        }
    }

    return true;
}

size_t LongestConsonantSequenceOf(const string& word) {
    size_t maxConsonantCount = 0;
    size_t consonantCounter = 0;

    for(char letter : word) {
        if(IsConsonant(letter)) {
            ++consonantCounter;

        } else {
            maxConsonantCount = max(consonantCounter, maxConsonantCount);
            consonantCounter = 0;
        }
    }

    return max(consonantCounter, maxConsonantCount);
}

class Program {
public:
    Program() {
        ifstream file("tekst.txt");

        for(string temp; file >> temp;) {
            words.push_back(move(temp));
        }

        cout << fixed << setprecision(2);
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        cout << "1) ";
        cout << count_if(words.begin(), words.end(), [](const string& word) {
            for(auto it = word.begin() + 1; it != word.end(); ++it) {
                if(*it == *(it - 1)) {
                    return true;
                }
            }

            return false;
        });
        cout << '\n';
    }

    void Task2() {
        map<char, size_t> letterCounter;
        size_t totalLetterCount = 0;

        for(auto&& word : words) {
            for(char letter : word) {
                ++letterCounter[letter];
                ++totalLetterCount;
            }
        }

        cout << "2)\n";

        for(auto [letter, count] : letterCounter) {
            const double percent = (count * 100.0) / totalLetterCount;
            cout << letter << ": " << count << " (" << percent << "%)\n";
        }
    }

    void Task3() {
        stable_sort(words.begin(), words.end(), [](const string& left, const string& right) {
            return LongestConsonantSequenceOf(left) > LongestConsonantSequenceOf(right);
        });

        const size_t maxConsonantCount = LongestConsonantSequenceOf(words.front());
        cout << "3)\nlongest subsequence: " << maxConsonantCount << '\n';

        const auto last = find_if_not(words.begin(), words.end(), [maxConsonantCount](const string& word) {
            return LongestConsonantSequenceOf(word) == maxConsonantCount;
        });

        cout << "word count: " << (last - words.begin()) << '\n';
        cout << "first: " << words.front() << '\n';
    }

    vector<string> words;
};

int main() {
    Program program;
    program.Run();
}