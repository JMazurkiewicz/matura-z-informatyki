#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class LineOfWords {
public:
    bool HasWordsOfSameLength() const {
        return count_if(words.begin() + 1, words.end(), [size = words.front().size()](const string& word) {
                   return word.size() == size;
               }) == words.size() - 1;
    }

    bool AreAnagrams() const {
        return count_if(words.begin() + 1, words.end(), [firstWord = words.front()](const string& word) {
                   return is_permutation(firstWord.begin(), firstWord.end(), word.begin(), word.end());
               }) == words.size() - 1;
    }

private:
    array<string, 5> words;

    friend istream& operator>>(istream& stream, LineOfWords& line) {
        copy_n(istream_iterator<string>{stream}, line.words.size(), line.words.begin());
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const LineOfWords& line) {
        copy_n(line.words.begin(), line.words.size(), ostream_iterator<string>{stream, " "});
        return stream;
    }
};

class Program {
public:
    Program() {
        ifstream file("anagram.txt");
        copy(istream_iterator<LineOfWords>{file}, istream_iterator<LineOfWords>{}, back_inserter(lines));
    }

    void Run() {
        Task1();
        Task2();
    }

private:
    void Task1() {
        cout << "1)\n";
        copy_if(lines.begin(), lines.end(), ostream_iterator<LineOfWords>{cout, "\n"},
                mem_fn(&LineOfWords::HasWordsOfSameLength));
    }

    void Task2() {
        cout << "2)\n";
        copy_if(lines.begin(), lines.end(), ostream_iterator<LineOfWords>{cout, "\n"},
                mem_fn(&LineOfWords::AreAnagrams));
    }

    vector<LineOfWords> lines;
};

int main() {
    Program program;
    program.Run();
}