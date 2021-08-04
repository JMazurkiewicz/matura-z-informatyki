#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

unsigned long AsULong(const string& word) {
    return stoul(word, nullptr, 2);
}

bool IsTooLarge(const string& word) {
    if(word.size() <= 16) {
        return false;
    }

    return any_of(word.begin(), word.end() - 16, [](char symbol) { return symbol == '1'; });
}

bool IsDuocyclic(const string& word) {
    const auto middle = word.begin() + (word.size() / 2);
    return equal(word.begin(), middle, middle, word.end());
}

bool IsIncorrect(const string& word) {
    for(auto it = word.begin(); it != word.end(); it += 4) {
        if(AsULong(string{it, it + 4}) > 9) {
            return true;
        }
    }

    return false;
}

class Program {
public:
    Program() {
        ifstream file("binarne.txt");
        copy(istream_iterator<string>{file}, istream_iterator<string>{}, back_inserter(sequences));
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        cout << "1)\n";
        cout << "ilosc: " << count_if(sequences.begin(), sequences.end(), IsDuocyclic) << '\n';

        vector<string>::const_iterator theLongest = find_if(sequences.begin(), sequences.end(), IsDuocyclic);

        for(auto it = theLongest + 1; it != sequences.end(); ++it) {
            if(IsDuocyclic(*it)) {
                theLongest = max(it, theLongest, [](auto left, auto right) { return left->size() < right->size(); });
            }
        }

        cout << "długosc najdluzszego: " << theLongest->size() << '\n';
        cout << "najdluzszy: " << *theLongest << '\n';
    }

    void Task2() {
        cout << "2)\n";
        cout << "ilosc: " << count_if(sequences.begin(), sequences.end(), IsIncorrect) << '\n';

        vector<string>::const_iterator theShortest = find_if(sequences.begin(), sequences.end(), IsIncorrect);

        for(auto it = theShortest + 1; it != sequences.end(); ++it) {
            if(IsIncorrect(*it)) {
                theShortest = min(it, theShortest, [](auto left, auto right) { return left->size() < right->size(); });
            }
        }

        cout << "najmniejsza dlugosc: " << theShortest->size() << '\n';
    }

    void Task3() {
        unsigned long maximum = AsULong(sequences.front());

        for(auto it = sequences.begin() + 1; it != sequences.end(); ++it) {
            if(!IsTooLarge(*it)) {
                maximum = max(AsULong(*it), maximum);
            }
        }

        cout << "3)\n";
        cout << "w systemie 10: " << maximum << '\n';
        cout << "w systemie 2: " << bitset<16>{maximum} << '\n';
    }

    vector<string> sequences;
};

int main() {
    Program program;
    program.Run();
}