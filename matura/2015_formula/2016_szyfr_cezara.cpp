#include <fstream>
#include <iostream>
#include <string>

using namespace std;

constexpr char EncryptLetter(char letter, int key) {
    const char stage1 = letter - 'A';
    const char stage2 = stage1 + key;
    const char stage3 = stage2 % 26;
    const char stage4 = stage3 + 'A';

    return stage4;
}

string Encrypt(const string& text, int key) {
    key %= 26;

    string result;

    for(char letter : text) {
        result += EncryptLetter(letter, key);
    }

    return result;
}

string Decrypt(const string& text, int key) {
    return Encrypt(text, 26 - key % 26);
}

constexpr int CalculateKey(char letter, char encryptedLetter) {
    const int stage1 = letter - encryptedLetter;
    const int stage2 = 26 - stage1;
    const int stage3 = stage2 % 26;

    return stage3;
}

bool IsProperlyEncrypted(const string& text, const string& encryptedText) {
    const int key = CalculateKey(text[0], encryptedText[0]);

    for(size_t index = 1; index != text.size(); ++index) {
        if(EncryptLetter(text[index], key) != encryptedText[index]) {
            return false;
        }
    }

    return true;
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
        cout << "Zadanie 6.1\n";
        ifstream file("dane_6_1.txt");

        size_t line = 1;
        for(string text; file >> text;) {
            cout << line++ << ")\t" << Encrypt(text, 107) << '\n';
        }

        cout << '\n';
    }

    void Task2() {
        cout << "Zadanie 6.2\n";
        ifstream file("dane_6_2.txt");

        string text;
        int key;

        size_t line = 1;
        while(file >> text >> key) {
            cout << line++ << ")\t" << Decrypt(text, key) << '\n';
        }

        cout << '\n';
    }

    void Task3() {
        cout << "Zadanie 6.3\n";
        ifstream file("dane_6_3.txt");

        size_t line = 1;
        for(string text, encryptedText; file >> text >> encryptedText;) {
            if(!IsProperlyEncrypted(text, encryptedText)) {
                cout << line++ << ")\t" << text << '\n';
            }
        }
    }
};

int main() {
    Program program;
    program.Run();
}