#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class Program {
public:
    Program() {
        ifstream file("dane.txt");
        copy(istream_iterator<string>{file}, istream_iterator<string>{}, back_inserter(numbers));
    }

    void Run() {
        Task1();
        Task2();
        Task3();
    }

private:
    void Task1() {
        cout << "1) " << count_if(numbers.begin(), numbers.end(), [](const string& number) {
            return number.front() == number.back();
        });
        cout << '\n';
    }

    void Task2() {
        cout << "2) " << count_if(numbers.begin(), numbers.end(), [](const string& number) {
            const string dec = to_string(stoi(number, nullptr, 8));
            return dec.front() == dec.back();
        });
        cout << '\n';
    }

    void Task3() {
        cout << "3) " << count_if(numbers.begin(), numbers.end(), [](const string& number) {
            for(auto it = number.begin() + 1; it != number.end(); ++it) {
                if(*it < *(it - 1)) {
                    return false;
                }
            }

            return true;
        });
        cout << '\n';
    }

    vector<string> numbers;
};

int main() {
    Program program;
    program.Run();
}