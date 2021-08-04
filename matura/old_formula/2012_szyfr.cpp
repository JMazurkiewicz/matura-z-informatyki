#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class CipherBase {
public:
    explicit CipherBase(const string& key)
        : key(key) { }

    string Transform(const string& input) {
        ResetIterator();
        string result(input.size(), '\0');

        transform(input.begin(), input.end(), result.begin(), [this](char letter) -> char {
            const char transformedLetter = TransformLetter(letter);
            IncrementIterator();
            return transformedLetter;
        });

        return result;
    }

protected:
    char KeyValue() const {
        return *keyIterator;
    }

    virtual char TransformLetter(char letter) const = 0;

private:
    void IncrementIterator() {
        ++keyIterator;
        if(keyIterator == key.end()) {
            keyIterator = key.begin();
        }
    }

    void ResetIterator() {
        keyIterator = key.begin();
    }

    const string key;
    string::const_iterator keyIterator;
};

class Encrypter : public CipherBase {
public:
    using CipherBase::CipherBase;

private:
    virtual char TransformLetter(char letter) const override final {
        letter += (KeyValue() - 'A' + 1);

        if(letter > 90) {
            letter -= 26;
        }

        return letter;
    }
};

class Decrypter : public CipherBase {
public:
    using CipherBase::CipherBase;

private:
    virtual char TransformLetter(char letter) const override final {
        letter -= (KeyValue() - 'A' + 1);

        if(letter < 65) {
            letter += 26;
        }

        return letter;
    }
};

class Program {
public:
    void Run() {
        TaskA();
        TaskB();
    }

private:
    void TaskA() {
        cout << "A)\n";

        ifstream wordsFile("tj.txt");
        ifstream keysFile("klucze1.txt");

        for(string word, key; (wordsFile >> word) && (keysFile >> key);) {
            Encrypter encrypter(key);
            cout << encrypter.Transform(word) << '\n';
        }

        cout << '\n';
    }

    void TaskB() {
        cout << "B)\n";

        ifstream wordsFile("sz.txt");
        ifstream keysFile("klucze2.txt");

        for(string word, key; (wordsFile >> word) && (keysFile >> key);) {
            Decrypter decrypter(key);
            cout << decrypter.Transform(word) << '\n';
        }
    }
};

int main() {
    Program program;
    program.Run();
}