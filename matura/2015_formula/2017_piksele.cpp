#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>

using namespace std;

constexpr size_t ROWS = 200;
constexpr size_t COLUMNS = 320;

bool AreContrasting(int left, int right) {
    return abs(left - right) > 128;
}

class Line {
public:
    int GetTheBrightest() const {
        return *max_element(data.begin(), data.end());
    }

    int GetTheDarkest() const {
        return *min_element(data.begin(), data.end());
    }

    bool IsSymmetric() const {
        return equal(data.begin(), data.begin() + (data.size() / 2), data.rbegin());
    }

    int operator[](size_t columnIndex) const {
        return data[columnIndex];
    }

private:
    friend istream& operator>>(istream& stream, Line& line) {
        copy_n(istream_iterator<int>{stream}, line.data.size(), line.data.begin());
        return stream;
    }

    array<int, COLUMNS> data;
};

class Program {
public:
    Program() {
        ifstream file("dane.txt");
        copy_n(istream_iterator<Line>{file}, lines.size(), lines.begin());
    }

    void Run() {
        Task1();
        Task2();
        Task3();
        Task4();
    }

private:
    void Task1() {
        cout << "1)\n";

        const int theBrightest = max_element(lines.begin(), lines.end(), [](const Line& left, const Line& right) {
                                     return left.GetTheBrightest() < right.GetTheBrightest();
                                 })->GetTheBrightest();

        cout << "the brightest: " << theBrightest << '\n';

        const int theDarkest = min_element(lines.begin(), lines.end(), [](const Line& left, const Line& right) {
                                   return left.GetTheDarkest() < right.GetTheDarkest();
                               })->GetTheDarkest();

        cout << "the darkest: " << theDarkest << '\n';
    }

    void Task2() {
        cout << "2) " << count_if(lines.begin(), lines.end(), not_fn(&Line::IsSymmetric)) << '\n';
    }

    void Task3() {
        const auto IsContrasting = [this](size_t rowIndex, size_t columnIndex) -> bool {
            const bool withUpper =
                rowIndex != 0 && AreContrasting(lines[rowIndex][columnIndex], lines[rowIndex - 1][columnIndex]);
            const bool withLower =
                rowIndex != ROWS - 1 && AreContrasting(lines[rowIndex][columnIndex], lines[rowIndex + 1][columnIndex]);
            const bool withLeft =
                columnIndex != 0 && AreContrasting(lines[rowIndex][columnIndex], lines[rowIndex][columnIndex - 1]);
            const bool withRight = columnIndex != COLUMNS - 1 &&
                                   AreContrasting(lines[rowIndex][columnIndex], lines[rowIndex][columnIndex + 1]);

            return withUpper || withLower || withLeft || withRight;
        };

        size_t counter = 0;

        for(size_t rowIndex = 0; rowIndex != ROWS; ++rowIndex) {
            for(size_t columnIndex = 0; columnIndex != COLUMNS; ++columnIndex) {
                if(IsContrasting(rowIndex, columnIndex)) {
                    ++counter;
                }
            }
        }

        cout << "3) " << counter << '\n';
    }

    void Task4() {
        const auto GetLongestSubsequenceInColumn = [this](size_t columnIndex) -> size_t {
            size_t maxLength = 0;
            size_t currentLength = 0;
            size_t currentElement = -1;

            for(size_t rowIndex = 0; rowIndex != ROWS; ++rowIndex) {
                if(lines[rowIndex][columnIndex] == currentElement) {
                    ++currentLength;

                } else {
                    maxLength = max(currentLength, maxLength);

                    currentLength = 1;
                    currentElement = lines[rowIndex][columnIndex];
                }
            }

            return max(currentLength, maxLength);
        };

        size_t maxLength = 0;

        for(size_t columnIndex = 0; columnIndex != COLUMNS; ++columnIndex) {
            maxLength = max(GetLongestSubsequenceInColumn(columnIndex), maxLength);
        }

        cout << "4) " << maxLength << '\n';
    }

    array<Line, ROWS> lines;
};

int main() {
    Program program;
    program.Run();
}