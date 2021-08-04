#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string Encrypt(const string& word, const vector<int>& key) {
    string result = word;

    for(size_t index = 0; index < word.size(); ++index) {
        const size_t keyIndex = key[index % key.size()] - 1;
        swap(result[index], result[keyIndex]);
    }

    return result;
}

string Decrypt(const string& word, const vector<int>& key) {
    string result = word;

    for(size_t index = result.size(); index-- > 0;) {
        const size_t keyIndex = key[index % key.size()] - 1;
        swap(result[index], result[keyIndex]);
    }

    return result;
}

class Program {
public:
    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        ifstream file("szyfr1.txt");

        array<string, 6> words;
        for(string& word : words) {
            file >> word;
        }

        vector<int> key(50);
        copy(istream_iterator<int>{file}, istream_iterator<int>{}, key.begin());

        cout << "1)\n";
        for(auto&& word : words) {
            cout << Encrypt(word, key) << '\n';
        }
    }

    void Task2() {
        ifstream file("szyfr2.txt");

        string word;
        file >> word;

        vector<int> key(15);
        copy(istream_iterator<int>{file}, istream_iterator<int>{}, key.begin());

        cout << "2) " << Encrypt(word, key) << '\n';
    }

    void Task3() {
        string word;
        ifstream("szyfr3.txt") >> word;

        cout << "3) " << Decrypt(word, {6, 2, 4, 1, 5, 3});
    }
};

int main() {
    Program program;
    program.Run();
}