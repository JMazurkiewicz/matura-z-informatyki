#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <string_view>

using namespace std;

class VigenereCipher {
public:
    explicit VigenereCipher(string_view key)
        : key(key)
        , keyRepeats(0) { }

    string Encrypt(string_view input) {
        return Transform(input, &VigenereCipher::EncryptLetter);
    }

    string Decrypt(string_view input) {
        return Transform(input, &VigenereCipher::DecryptLetter);
    }

    size_t GetKeyRepeats() const {
        return keyRepeats;
    }

private:
    string Transform(string_view input, char (VigenereCipher::*transformFunction)(char)) {
        ResetKey();

        string result;
        transform(input.begin(), input.end(), back_inserter(result), [transformFunction, this](char letter) -> char {
            if(!isupper(letter)) {
                return letter;
            }

            letter = (this->*transformFunction)(letter);

            IncrementKeyIterator();
            return letter;
        });

        return result;
    }

    char EncryptLetter(char letter) {
        const char key = *keyIterator - 'A';
        letter -= 'A';

        letter = (letter + key) % 26;

        return letter + 'A';
    }

    char DecryptLetter(char letter) {
        const char key = *keyIterator - 'A';
        letter -= 'A';

        letter = (letter - key);
        if(letter < 0) {
            letter = 26 + letter;
        }

        return letter + 'A';
    }

    void ResetKey() {
        keyRepeats = 1;
        keyIterator = key.begin();
    }

    void IncrementKeyIterator() {
        ++keyIterator;

        if(keyIterator == key.end()) {
            ++keyRepeats;
            keyIterator = key.begin();
        }
    }

    string_view key;
    string_view::const_iterator keyIterator;

    size_t keyRepeats;
};

class Program {
public:
    Program() {
        ifstream file("szyfr.txt");

        getline(file, text);
        getline(file, key);
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        string text;
        getline(ifstream{"dokad.txt"}, text);

        VigenereCipher cipher("LUBIMYCZYTAC");

        cout << "1)\n";
        cout << cipher.Encrypt(text) << '\n';
        cout << "repeats: " << cipher.GetKeyRepeats() << '\n';
    }

    void Task2() {
        VigenereCipher cipher(key);
        cout << "2)\n" << cipher.Decrypt(text) << '\n';
    }

    void Task3() {
        map<char, size_t> letterCounter;
        size_t totalLetterCounter = 0;

        for(char letter : text) {
            if(isupper(letter)) {
                ++letterCounter[letter];
                ++totalLetterCounter;
            }
        }

        cout << "3)\na)\n";
        for(auto [letter, count] : letterCounter) {
            cout << letter << ": " << count << '\n';
        }

        double kIndex = 0;
        for(auto [letter, count] : letterCounter) {
            kIndex += count * (count - 1);
        }
        kIndex /= totalLetterCounter * (totalLetterCounter - 1);

        const double possibleLength = 0.0285 / (kIndex - 0.0385);

        cout << fixed << setprecision(2);
        cout << "b)\n";
        cout << "key length: " << key.size() << '\n';
        cout << "possible key length: " << possibleLength << '\n';
    }

    string text;
    string key;
};

int main() {
    Program program;
    program.Run();
}