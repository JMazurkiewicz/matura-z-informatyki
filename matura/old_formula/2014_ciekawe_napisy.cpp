#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

constexpr bool IsPrime(unsigned long value) {
    if(value == 1) {
        return false;
    }

    for(unsigned long div = 2; div * div <= value; ++div) {
        if(value % div == 0) {
            return false;
        }
    }

    return true;
}

class Program {
public:
    Program() {
        ifstream file("NAPIS.txt");
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
            return IsPrime(accumulate(word.begin(), word.end(), 0UL));
        });
        cout << '\n';
    }

    void Task2() {
        cout << "2) ";
        copy_if(words.begin(), words.end(), ostream_iterator<string>{cout, "\n"},
                [](const string& word) { return is_sorted(word.begin(), word.end()); });
    }

    void Task3() {
        map<string, size_t> wordCounter;

        for(auto&& word : words) {
            ++wordCounter[word];
        }

        cout << "3)\n";
        for(auto [word, count] : wordCounter) {
            if(count > 1) {
                cout << word << '\n';
            }
        }
    }

    vector<string> words;
};

int main() {
    Program program;
    program.Run();
}