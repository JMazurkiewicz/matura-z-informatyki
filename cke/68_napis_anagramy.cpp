#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

bool IsMonolit(const string& word) {
    return word.find_first_not_of(word.back()) == string::npos;
}

class Program {
public:
    Program() {
        ifstream file("dane_napisy.txt");

        for(string temp; file >> temp;) {
            sort(temp.begin(), temp.end());
            words.push_back(move(temp));
        }
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        size_t counter = 0;

        for(size_t index = 0; index < words.size(); index += 2) {
            const string& word1 = words[index];
            const string& word2 = words[index + 1];

            if(word1 == word2 && IsMonolit(word1) && IsMonolit(word2)) {
                ++counter;
            }
        }

        cout << "1) " << counter << '\n';
    }

    void Task2() {
        size_t counter = 0;

        for(size_t index = 0; index < words.size(); index += 2) {
            if(words[index] == words[index + 1]) {
                ++counter;
            }
        }

        cout << "2) " << counter << '\n';
    }

    void Task3() {
        sort(words.begin(), words.end());

        size_t mostCommonMaxCounter = 0;

        size_t mostCommonCounter = 0;
        string_view mostCommonAnagram = words.back();

        for(auto&& word : words) {
            if(word == mostCommonAnagram) {
                ++mostCommonCounter;

            } else {
                mostCommonMaxCounter = max(mostCommonCounter, mostCommonMaxCounter);

                mostCommonCounter = 1;
                mostCommonAnagram = word;
            }
        }

        cout << "3) " << mostCommonMaxCounter << '\n';
    }

    vector<string> words;
};

int main() {
    Program program;
    program.Run();
}