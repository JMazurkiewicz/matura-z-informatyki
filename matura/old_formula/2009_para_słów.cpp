#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsPalindrome(const string& word) {
    return equal(word.begin(), word.begin() + (word.size() / 2), word.rbegin());
}

bool Contains(const string& one, const string& two) {
    return one.find(two) != string::npos;
}

bool StartsWith(const string& one, const string& two) {
    return one.size() >= two.size() && one.compare(0, two.size(), two) == 0;
}

bool EndsWith(const string& one, const string& two) {
    return one.size() >= two.size() && one.compare(one.size() - two.size(), string::npos, two) == 0;
}

class WordAdder {
public:
    WordAdder(const string& one, const string& two)
        : one(one)
        , two(two) { }

    WordAdder(const WordAdder&) = delete;

    string Add() {
        if(Contains(one, two)) {
            return one;
        }

        const string prefixMethod = TryPrefixMethod();
        const string suffixMethod = TrySuffixMethod();

        if(prefixMethod.size() < suffixMethod.size()) {
            return prefixMethod;
        } else {
            return suffixMethod;
        }
    }

private:
    string TryPrefixMethod() {
        size_t pos = 0;

        while(pos < two.size()) {
            if(StartsWith(one, two.substr(pos))) {
                break;
            }

            ++pos;
        }

        return two.substr(0, pos) + one;
    }

    string TrySuffixMethod() {
        size_t pos = two.size();

        while(pos >= 1) {
            if(EndsWith(one, two.substr(0, pos))) {
                break;
            }

            --pos;
        }

        return one + two.substr(pos);
    }

    const string& one;
    const string& two;
};

class Program {
public:
    void Run() {
        LoadDataFromFile();

        cout << "a) " << DoTaskA() << '\n';
        cout << "b) " << DoTaskB() << '\n';
        cout << "c) " << DoTaskC() << '\n';
        cout << "d)\n";
        DoTaskD();
    }

private:
    void LoadDataFromFile() {
        ifstream file("dane.txt");

        for(string temp; file >> temp;) {
            words.push_back(temp);
        }
    }

    size_t DoTaskA() {
        size_t palindromeCounter{};
        for(auto&& e : words) {
            if(IsPalindrome(e)) {
                ++palindromeCounter;
            }
        }

        return palindromeCounter;
    }

    size_t DoTaskB() {
        size_t counter = 0;

        for(size_t i = 0; i < words.size(); i += 2) {
            if(Contains(words[i], words[i + 1])) {
                ++counter;
            }
        }

        return counter;
    }

    size_t DoTaskC() {
        size_t counter = 0;

        for(size_t i = 0; i < words.size(); i += 2) {
            const string& a = words[i];
            const string& b = words[i + 1];

            WordAdder adder(a, b);
            const string c = adder.Add();

            if(c == a + b || c == b + a) {
                ++counter;
            }
        }

        return counter;
    }

    void DoTaskD() {
        for(size_t i = 0; i < words.size(); i += 2) {
            WordAdder adder(words[i], words[i + 1]);
            cout << adder.Add() << '\n';
        }
    }

    vector<string> words;
};

int main() {
    ios_base::sync_with_stdio(false);

    Program program;
    program.Run();
}