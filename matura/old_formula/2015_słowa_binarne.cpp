#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

size_t LongestSubsequenceOfZeros(const string& word) {
    size_t longest = 0;
    size_t currentLongest = 0;

    for(auto it = word.begin(); it != word.end(); ++it) {
        if(*it == '0') {
            ++currentLongest;

        } else {
            longest = max(longest, currentLongest);
            currentLongest = 0;
        }
    }

    return max(longest, currentLongest);
}

class Program {
public:
    Program() {
        ifstream file("slowa.txt");
        copy(istream_iterator<string>{file}, istream_iterator<string>{}, back_inserter(words));
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        cout << "1) " << count_if(words.begin(), words.end(), [](const string& word) {
            return count(word.begin(), word.end(), '0') > count(word.begin(), word.end(), '1');
        });
        cout << '\n';
    }

    void Task2() {
        cout << "2) " << count_if(words.begin(), words.end(), [](const string& word) {
            if(word.front() != '0' || word.back() != '1') {
                return false;
            }

            return find_if_not(word.begin(), word.end(), bind(equal_to<char>{}, placeholders::_1, '0')) ==
                   find_if_not(word.rbegin(), word.rend(), bind(equal_to<char>{}, placeholders::_1, '1')).base();
        });
        cout << '\n';
    }

    void Task3() {
        const size_t longestSubsequenceOfZeros = LongestSubsequenceOfZeros(
            *max_element(words.begin(), words.end(), [](const string& left, const string& right) {
                return LongestSubsequenceOfZeros(left) < LongestSubsequenceOfZeros(right);
            }));

        cout << "3)\n";
        cout << "longest: " << longestSubsequenceOfZeros << '\n';
        copy_if(words.begin(), words.end(), ostream_iterator<string>{cout, "\n"},
                [longestSubsequenceOfZeros](const string& word) {
                    return LongestSubsequenceOfZeros(word) == longestSubsequenceOfZeros;
                });
    }

    vector<string> words;
};

int main() {
    Program program;
    program.Run();
}