#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

constexpr bool PRINT = true;

class Message {
public:
    istream& LoadText(istream& stream) {
        return getline(stream, text);
    }

    istream& LoadSignature(istream& stream) {
        copy_n(istream_iterator<int>{stream}, signature.size(), signature.begin());
        return stream;
    }

    string MakeAbbreviationOfText(bool print = false) const {
        string text = this->text;
        string result = "ALGORYTM";

        while(text.size() % 8 != 0) {
            text.push_back('.');
        }

        if(print) {
            cout << text.size() << '\n';
        }

        for(size_t p = 0; p < text.size(); p += 8) {
            for(size_t q = 0; q < 8; ++q) {
                result[q] = (result[q] + text[p + q]) % 128;
            }
        }

        if(print) {
            for(char symbol : result) {
                cout << static_cast<int>(symbol) << ' ';
            }
            cout << '\n';
        }

        for(char& symbol : result) {
            symbol = 65 + symbol % 26;
        }

        return result;
    }

    string MakeAbbreviationOfSignature() const {
        string result(signature.size(), '\0');

        transform(signature.begin(), signature.end(), result.begin(),
                  [](int signaturePart) { return 3 * signaturePart % 200; });

        return result;
    }

private:
    string text;
    array<int, 8> signature;
};

class Program {
public:
    Program() {
        ifstream file1("podpisy.txt");
        ifstream file2("wiadomosci.txt");

        for(Message message; message.LoadSignature(file1) && message.LoadText(file2);) {
            messages.push_back(move(message));
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

        const string abbreviation = messages[0].MakeAbbreviationOfText(PRINT);
        cout << abbreviation << '\n';
    }

    void Task2() {
        cout << "2)\n";

        for(auto&& message : messages) {
            cout << message.MakeAbbreviationOfSignature() << '\n';
        }
    }

    void Task3() {
        cout << "3)\n";
        for(size_t index = 0; index < messages.size(); ++index) {
            if(messages[index].MakeAbbreviationOfSignature() == messages[index].MakeAbbreviationOfText()) {
                cout << index + 1 << ' ';
            }
        }
        cout << '\n';
    }

    vector<Message> messages;
};

int main() {
    Program program;
    program.Run();
}