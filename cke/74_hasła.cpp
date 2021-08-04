#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool HasTask3Subsequence(const string& password) {
    for(auto p = password.begin(); p != password.end() - 3; ++p) {
        string temp(p, p + 4);
        sort(temp.begin(), temp.end());

        if(temp[0] + 1 == temp[1] && temp[1] + 1 == temp[2] && temp[2] + 1 == temp[3]) {
            return true;
        }
    }

    return false;
}

class Program {
public:
    Program() {
        ifstream file("hasla.txt");

        for(string temp; file >> temp;) {
            passwords.push_back(move(temp));
        }
    }

    void Run() {
        Task1();
        Task2();
        Task3();
        Task4();
    }

private:
    void Task1() {
        cout << "1) " << count_if(passwords.begin(), passwords.end(), [](const string& password) {
            return all_of(password.begin(), password.end(), [](unsigned char c) { return isdigit(c) != 0; });
        });
        cout << '\n';
    }

    void Task2() {
        sort(passwords.begin(), passwords.end());

        cout << "2)\n";

        for(auto p = passwords.begin() + 1; p != passwords.end(); ++p) {
            if(*p == *(p - 1)) {
                cout << *p << '\n';
            }
        }
    }

    void Task3() {
        cout << "3) " << count_if(passwords.begin(), passwords.end(), HasTask3Subsequence) << '\n';
    }

    void Task4() {
        cout << "4) " << count_if(passwords.begin(), passwords.end(), [](const string& password) {
            bool has_upper = false;
            bool has_lower = false;
            bool has_digit = false;

            for(char c : password) {
                if(isupper(c) != 0) {
                    has_upper = true;
                } else if(islower(c) != 0) {
                    has_lower = true;
                } else if(isdigit(c) != 0) {
                    has_digit = true;
                }
            }

            return has_upper && has_lower && has_digit;
        });
    }

    vector<string> passwords;
};

int main() {
    Program program;
    program.Run();
}