#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string Encrypt(const string& word, int factor, int shift) {
    string result = word;

    for(char& letter : result) {
        const int stage1 = letter - 'a';
        const int stage2 = stage1 * factor + shift;
        const int stage3 = (stage2 % 26) + 'a';

        letter = stage3;
    }

    return result;
}

pair<int, int> FindKeyFor(const string& decrypted, const string& encrypted) {
    int factor, shift;

    for(factor = 0; factor <= 25; ++factor) {
        bool out = false;

        for(shift = 0; shift <= 25; ++shift) {
            if(Encrypt(decrypted, factor, shift) == encrypted) {
                out = true;
                break;
            }
        }

        if(out) {
            break;
        }
    }

    return {factor, shift};
}

class Program {
public:
    Program() {
        ifstream file("tekst.txt");

        for(string temp; file >> temp;) {
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
        cout << "1)\n";

        copy_if(words.begin(), words.end(), ostream_iterator<string>(cout, "\n"), [](const string& word) {
            return (word.front() == 'd' && word.back() == 'd');
        });
    }

    void Task2() {
        cout << "2)\n";

        for(auto&& word : words) {
            if(word.size() >= 10) {
                cout << Encrypt(word, 5, 2) << '\n';
            }
        }
    }

    void Task3() {
        ifstream file("probka.txt");
        size_t counter = 1;

        cout << "3)\n";

        for(string decrypted, encrypted; file >> decrypted >> encrypted;) {
            auto [factorDec, shiftDec] = FindKeyFor(decrypted, encrypted);
            auto [factorEnc, shiftEnc] = FindKeyFor(encrypted, decrypted);

            cout << counter << " -> encrypt";
            cout << '(' << factorDec << ", " << shiftDec << "), decrypt";
            cout << '(' << factorEnc << ", " << shiftEnc << ")\n";

            ++counter;
        }
    }

    vector<string> words;
};

int main() {
    Program program;
    program.Run();
}